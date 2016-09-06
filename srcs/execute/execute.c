/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/06 15:39:37 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	try_parent_builtin(t_shell *s)
{
	int		ret;
	char	*tmp;

	if (ft_strcmp(s->input[0], "cd") == 0)
		return (ft_cd(s->input, s));
	else if (ft_strcmp(s->input[0], "exit") == 0)
	   return (EXIT_SH);
//	else if (ft_strcmp(s->input[0], "set") == 0 && !s->input[1])
//		return (ft_set(2, NULL, NULL, s));
	else if (ft_strcmp(s->input[0], "setenv") == 0)
		return (ft_set(1, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "export") == 0)
	{
		tmp = ft_strdup(ft_getenv(s->input[1], s));
		ret = ft_set(1, s->input[1], tmp, s);
		ft_strdel(&tmp);
		return (ret);
	}
	else if (ft_strcmp(s->input[0], "unsetenv") == 0)
		return (ft_unsetenv(s->input[1], s));
	else
		return (ERR_NOTFOUND);
}

static int	try_child_builtin(t_shell *s)
{
	if (ft_strcmp(s->input[0], "echo") == 0)
		return (ft_echo(s->input, s));
	else if (ft_strcmp(s->input[0], "env") == 0)
		return (ft_env(s->input, s));
//	else if (ft_strcmp(s->input[0], "set") == 0)
//		return (ft_set(2, s->input[1], s->input[1], s));
//	else if (ft_strcmp(s->input[0], "setenv") == 0)
//		return (ft_set(1, s->input[1], s->input[2], s));
/*	else if (ft_strcmp(s->input[0], "export") == 0)
	{
		tmp = ft_strdup(ft_getenv(s->input[1], s));
		ret = ft_set(1, s->input[1], tmp, s);
		ft_strdel(&tmp);
		return (ret);
	}
	else if (ft_strcmp(s->input[0], "unsetenv") == 0)
		return (ft_unsetenv(s->input[1], s));
	else if (ft_strcmp(s->input[0], "unset") == 0)
		return (ft_unsetenv(s->input[1], s));
*/	else
		return (ERR_NOTFOUND);
}

static void	make_path_and_execute(char *path, t_shell *s)
{
	int				i;
	char			*tmp;
	t_split_string	sp;

	i = 0;
	sp = ft_nstrsplit(path, ':');
	if (s->paths)
		free_tab((void ***)&s->paths, ft_tablen(s->paths));
	s->paths = ft_tabdup(sp.strings, sp.words);
	free_tab((void ***)&sp.strings, sp.words);
	while (s->paths[++i] != NULL)
	{
		tmp = ft_strjoinstr(s->paths[i], "/", s->input[0]);
		if (access(tmp, F_OK) == 0)
			if (check_rights(tmp, 'r', 0, 'x') == EXIT_SUCCESS)
				if (execve(tmp, s->input, s->env_var) != -1)
				{
					ft_strdel(&tmp);
					free_t_shell(s);
				}
		ft_strdel(&tmp);
	}
}

static int	try_system(t_shell *s)
{
	char	*tmp;

//dprintf(2, "try_system() -- trying '%s'\n", s->input[0]); // debug
	if (access(s->input[0], F_OK) == 0)
	{
		if (check_rights(s->input[0], 'r', 0, 'x') == EXIT_SUCCESS)
			if (execve(s->input[0], s->input, s->env_var) != -1)
				free_t_shell(s);
	}
	else
		if ((tmp = ft_getenv("PATH", s)))
			make_path_and_execute(tmp, s);
	return (ERR_NOTFOUND);
}

int	execute_cmd(t_shell *s)
{
	pid_t	pid;
	int		status;
	int		i;

	status = EXIT_FAILURE;
	if ((status = try_parent_builtin(s)) == ERR_NOTFOUND)
	{
		if ((pid = fork()) < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
		{
			s->fork_pid = getpid();
//dprintf(2, "--- START -- CHILD PROCESS --- ppid = %d\tpid = %d\n"
//						"execute_cmd() - child -- Trying to execute '%s' with '%s' ...\n",
//						getppid(), getpid(), s->input[0], s->input[1]); // debug
				if (s->pipe.n_pipes)
					child_pipe(s);
				if (s->redir.n_rdr)
				{
					i = s->redir.rdr_i;
					if (s->redir.dir == '>')
						child_output_redir(s->redir.rdr[i], s);
					else if (s->redir.dir == '<')
					{
						child_input_redir(s->redir.rdr[i], s);
					}
				}
				if ((status = try_child_builtin(s)) == ERR_NOTFOUND)
                {
                    tputs(tgetstr("cr", 0), 1, ft_putchar_re);
                    tputs(tgetstr("ce", 0), 1, ft_putchar_re);
					status = try_system(s);
                }
		// child has executed and written to the output fd required, whether its for a pipe, redir or screen.
//dprintf(2, "--- CHILD PROCESS returning, not exited --- ppid = %d\tpid = %d\n", getppid(), getpid()); // debug
//dprintf(2, "2 - child -- status = '%d'\tpid = %d\n", status, getpid()); // debug
			free_t_shell(s);
//dprintf(2, "2 - child -- status = '%d'\tstatus(-900) = '%d'\tpid = %d\n", status, status-900, getpid()); // debug
			exit(status == 0 ? 0 : (status - 900));
		}
		// -----   Parent only   ------

//dprintf(2, "execute_cmd() -- Parent only area ------- ppid = %d\tpid = %d\n", getppid(), getpid()); // debug
		if (s->pipe.n_pipes)// if no redirs, then do pipes if there are any..
		{
//dprintf(2, "execute_cmd() -- Parent only area -- Do pipe  n_pipes = '%d' --- ppid = %d\tpid = %d\n", s->pipe.n_pipes, getppid(), getpid()); // debug
			parent_pipe(s);
		}
//	wait for child to finish
//dprintf(2, "execute_cmd() -- Waiting for child ------- pid = %d\n", getpid()); // debug
		wait(&status);
//dprintf(2, "execute_cmd() -- Finished waiting ------- pid = %d\n", getpid()); // debug

// error checks
		if (WIFEXITED(status) && (status = WEXITSTATUS(status)) != EXIT_SUCCESS)
		{
//dprintf(2, "1 -- status = '%d' status(+900) = '%d'\tpid = %d\n", status , status + 900, getpid()); // debug
			return (err(((status == 1) ? 1 : status + 900), s->input[0]));
//			return (err(status, s->input[0]));
		}
//dprintf(2, "2 -- status = '%d' status(+900) = '%d'\tpid = %d\n", status , status + 900, getpid()); // debug
	}
    tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	return (status);
}

