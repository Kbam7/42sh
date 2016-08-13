/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/13 01:30:42 by kbamping         ###   ########.fr       */
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
			{
				if (execve(path, s->input, var) != -1)
				{
					ft_strdel(&path);
					free_t_shell(s);
				}
				exit(EXIT_SUCCESS);
			}
		ft_strdel(&path);
	}
	free_tab((void **)s->input, ft_tablen(s->input));
	free_t_shell(s);
	exit(EXIT_FAILURE);
}



int	execute_cmd(t_shell *s)
{
	pid_t	pid;
	int		status;
	int		i;

	status = EXIT_FAILURE;

	if ((status = try_builtin(s)) == ERR_NOTFOUND)
	{
		pid = fork();
		if (pid < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
		{
//dprintf(2, "--- CHILD PROCESS ---\nexecute_cmd() -- Trying to execute '%s' with '%s' ...\n", s->input[0], s->input[1]); // debug
		// child only
			if (s->redir.n_rdr) // if theres redirs, do them FIRST!
			{
				i = s->redir.rdr_i;
				if (s->redir.dir == '>')
					child_output_redir(s->redir.rdr[i], s);
				else if (s->redir.dir == '<')
				{
					// read from s->redir.in_fd(s->redir.cmd i + 1]) into STDIN_FILENO for s->redir.cmd[i]
				//	child_input_redir(s->redir.rdr[i], s);
				}
			}
			else if (s->pipe.n_pipes)// else if no redirs, are there pipes? If yes, use it.
				child_pipe(s);

			try_system(s);
		// child has executed and written to the output fd required, whether its for a pipe, redir or screen.
		}
		
// -----   Parent only   ------

		if (!s->redir.n_rdr && s->pipe.n_pipes)// if no redirs, then do pipes if there are any..
		{
			parent_pipe(s);
		}
//	wait for child to finish
		wait(&status);
// error checks
		if (WIFEXITED(status) && (status = WEXITSTATUS(status)) == EXIT_FAILURE)
				return (err(ERR_NOTFOUND, s->input[0]));

		if (s->redir.n_rdr) // if theres redirs
		{
			i = s->redir.rdr_i;
			if (s->redir.dir == '>')
				status = parent_output_redir(s->redir.rdr[i], s);
			else if (s->redir.dir == '<')
			{
			//	status = parent_input_redir(s->redir.rdr[i], s);
			}
		}

// error checks
		if (status != EXIT_SUCCESS)
				return (err(status, s->input[0]));


	}
	return (status);
}

