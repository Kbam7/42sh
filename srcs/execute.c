/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/16 00:47:50 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	check_builtin_env_funcs(t_shell *s)
{
	char	*tmp;
	int		ret;
	
	if (ft_strcmp(s->input[0], "env") == 0)
		return (ft_env(s->input, s));
	else if (ft_strcmp(s->input[0], "set") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
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
	else if (ft_strcmp(s->input[0], "unset") == 0)
		return (ft_unsetenv(s->input[1], s));
	else
		return (ERR_NOTFOUND);
}

int	try_builtin(t_shell *s)
{
	int	ret;

	if (ft_strcmp(s->input[0], "cd") == 0)
		return (ft_cd(s->input, s));
	else if (ft_strcmp(s->input[0], "echo") == 0)
		return (ft_echo(s->input, s));
	else if (ft_strcmp(s->input[0], "21sh") == 0)
		return (run_shell(s));
	else if ((ret = check_builtin_env_funcs(s)) != ERR_NOTFOUND)
		return (ret);
	else
		return (ft_strcmp(s->input[0], "exit") == 0 ? EXIT_SH : ERR_NOTFOUND);
}

int	try_system(t_shell *s)
{
	int		i;
	char	*path;
	char	**var;

	var = (ft_strcmp(s->input[0], "printenv") == 0) ?
													s->env_var : s->shell_var;
	i = -1;
	while (s->paths[++i] != NULL)
	{
		path = ft_strjoinstr(s->paths[i], "/", s->input[0]);
		if (access(path, F_OK) == 0)
			if (check_rights(path, 'r', 0, 'x') == EXIT_SUCCESS)
				if (execve(path, s->input, var) != -1)
				{
					ft_strdel(&path);
					free_t_shell(s);
				}
		ft_strdel(&path);
	}
	return (ERR_NOTFOUND);
}



int	execute_cmd(t_shell *s)
{
	pid_t	pid;
	int		status;
	int		i;

//	status = EXIT_FAILURE; Possibly not needed as it is initialized in the next line
		if ((pid = fork()) < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
		{
//dprintf(2, "--- START -- CHILD PROCESS --- ppid = %d\tpid = %d\n"
//			"execute_cmd() - child -- Trying to execute '%s' with '%s' ...\n", getppid(), getpid(), s->input[0], s->input[1]); // debug
				if (s->pipe.n_pipes)
					child_pipe(s);
				if (s->redir.n_rdr)
				{
					i = s->redir.rdr_i;
					if (s->redir.dir == '>')
						child_output_redir(s->redir.rdr[i], s);
					else if (s->redir.dir == '<')
					{
//						child_input_redir(s->redir.rdr[i], s);
					}
				}
				if ((status = try_builtin(s)) == ERR_NOTFOUND)
					status = try_system(s);
		// child has executed and written to the output fd required, whether its for a pipe, redir or screen.
//dprintf(2, "--- CHILD PROCESS returning, not exited --- ppid = %d\tpid = %d\n", getppid(), getpid()); // debug
//dprintf(2, "2 - child -- status = '%d'\tpid = %d\n", status, getpid()); // debug
			free_t_shell(s);
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
//dprintf(2, "1 -- status = '%d'\tpid = %d\n", status + 900, getpid()); // debug
			return (err(((status == 1) ? 1 : status + 900), s->input[0]));
//			return (err(status, s->input[0]));
		}
//dprintf(2, "2 -- status = '%d'\tpid = %d\n", status + 900, getpid()); // debug
	return (status);
}

