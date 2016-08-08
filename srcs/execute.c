/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/09 00:54:45 by kbamping         ###   ########.fr       */
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
		return (ft_set(2, s->input[1], s->input[2], s));
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
				{
					child_output_redir(s->redir.rdr[i], s);
				}
				else if (s->redir.dir == '<')
				{
					// read from s->redir.in_fd(s->redir.cmd i + 1]) into STDIN_FILENO for s->redir.cmd[i]
				//	child_input_redir(s->redir.rdr[i], s);
				}
			}
			else if (s->pipe.n_pipes)// else if no redirs, are there pipes? If yes, use it.
			{
				i = s->pipe.pipe_i;
				if (i == 0) // first cmd
				{
					dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
					close(s->pipe.pipes[i][0]);						// close STDOUT and write to pipe[i + 1]
					close(s->pipe.pipes[i][1]);						// close STDOUT and write to pipe[i + 1]
				}
				else if (s->pipe.n_pipes == 1) // last pipe
				{
					dup2(s->pipe.pipes[i][0], STDIN_FILENO); // read from current pipe
					close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
					close(s->pipe.pipes[i][1]);	// close last write-end, STDOUT used
				}
				else
				{
					close(s->pipe.pipes[i][1]);	// close this pipe, writing to next pipe
					dup2(s->pipe.pipes[i][0], STDIN_FILENO); // read from current pipe
					close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
					dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
				}
				try_system(s);
			}
			else	// NO redirs and NO pipes EXIST !!
				try_system(s);
		// child has executed and written to the output fd required, whether its for a pipe, redir or screen.
		}
		
// -----   Parent only   ------

		if (s->redir.n_rdr) // if theres redirs, do them FIRST!
		{
			// nothing yet
		}
		else if (s->pipe.n_pipes)// else if no redirs, are there pipes? If yes, use it.
		{
			i = s->pipe.pipe_i;
			if (i == 0) // first cmd
			{
					close(s->pipe.pipes[i][0]);		// close pipe[0], not reading from first pipe
					close(s->pipe.pipes[i][1]);		// close pipe[1], not writing to first pipe
			}
			else if (s->pipe.n_pipes == 1) // last pipe
			{
					close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
					close(s->pipe.pipes[i][1]);	// close last write-end, STDOUT used
			}
			else
			{
					close(s->pipe.pipes[i][0]);	// STDIN reading from pipe[i][0]
					close(s->pipe.pipes[i][1]);	// STDOUT writing to pipe[i +1][1]
			}
		}
		else	// NO redirs and NO pipes EXIST !!
		{
			// something here
		}
//	Just wait for child and check its exit status.
		wait(&status);
// error checks
		if (WIFEXITED(status) && (status = WEXITSTATUS(status)) == EXIT_FAILURE)
				return (err(ERR_NOTFOUND, s->input[0]));
	}
	return (status);
}

/* START -- execute_utils.c */

int		child_output_redir(char *str, t_shell *s)
{
	// execute this inside child process
	// this function must be executed just before executing the command
	//	this function will create the necessary redirect (pipe) for the current redir
	// write output to pipe
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '>')
		++i;
	if (str[i] == '>')
	{
		if (i == 1 && str[i - 1] == '&')	// ('&>')
		{
		// redir STDOUT && STDERR of s->redir.cmd[i] to s->redir.cmd[i + 1]

		// check if string contains another '&', if it does, then error
			dup2(s->redir.pipe[i + 1][1], STDOUT_FILENO);
			dup2(s->redir.pipe[i + 1][1], STDERR_FILENO);
			close(s->redir.pipe[i + 1][1]);	// not needed, dupliated and redirected STDOUT to duplicate pipe
			close(s->redir.pipe[i][0]);		// not reading from current pipe
			close(s->redir.pipe[i][1]);		// not writing to current pipe
		}
		if (i == 0)	// (' >..')
		{
			// no FD defined, redir STDOUT fd(1), to destination
			dup2(s->redir.pipe[i + 1][1], STDOUT_FILENO);
			close(s->redir.pipe[i + 1][1]);
			close(s->redir.pipe[i][0]);
			close(s->redir.pipe[i][1]);
		}
		if (str[i + 1] == '>')	// ('>>')
		{
			//	append to output destination
			//	s->redir.rdr_i + 1
			++i;
		}
		if (str[i + 1] == '&')	// ('>&' || '>>&')
		{
			// ampersand
			++i;
		}
	}
	else if (str[i] == '<')
	{
	}
	return (EXIT_SUCCESS);
}

/* END -- execute_utils.c */
