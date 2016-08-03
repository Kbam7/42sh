/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/03 14:02:23 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"


int	check_builtin_env_funcs(t_shell *s)
{

printf("Checkin in builtin_env_funcs '%s' with '%s' ...", s->input[0], s->input[1]); // debug

	if (ft_strcmp(s->input[0], "env") == 0)
		return (ft_env(s->input, s));
	else if (ft_strcmp(s->input[0], "set") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "setenv") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "export") == 0)
		return (ft_set(1, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "unsetenv") == 0)
		return (ft_unsetenv(s->input[1], s));
	else if (ft_strcmp(s->input[0], "unset") == 0)
		return (ft_unsetenv(s->input[1], s));
	else
		return (ERR_NOTFOUND);
}

/*
int	check_assign_variable(t_shell *s)
{
	int	i;

	i  0;
	while (s->input[i])
		if (ft_strchr(s->input[i], '='))
	else
		return (ERR_NOTFOUND);
}
*/

int	try_builtin(t_shell *s)
{
	int	ret;

printf("Checkin in builtin_funcs '%s' with '%s' ...", s->input[0], s->input[1]); // debug

	if (ft_strcmp(s->input[0], "cd") == 0)
		return (ft_cd(s->input, s));
	else if (ft_strcmp(s->input[0], "echo") == 0)
		return (ft_echo(s->input, s));
	else if (ft_strcmp(s->input[0], "21sh") == 0)
		return (run_shell(s));
	else if ((ret = check_builtin_env_funcs(s)) != ERR_NOTFOUND)
		return (ret);
//	else if ((ret = check_assign_variable(s)) != ERR_NOTFOUND)
//		return (ret);
	else
		return (ft_strcmp(s->input[0], "exit") == 0 ? EXIT_SH : ERR_NOTFOUND);
}

int		try_system(t_shell *s)
{
	int		i;
	char	*path;
	char	**var;

	i = 0;
	var = (ft_strcmp(s->input[0], "printenv") == 0) ?
													s->env_var : s->shell_var;
	while (s->paths[i] != NULL)
	{
		path = ft_strjoinstr(s->paths[i], "/", s->input[0]);
		if (access(path, F_OK) == 0)
			if (check_rights(path, 'r', 0, 'x') == EXIT_SUCCESS)
			{
				if (execve(path, s->input, var) != -1)
					ft_strdel(&path);
				exit(EXIT_SUCCESS);
			}
		ft_strdel(&path);
		++i;
	}
	free_tab((void **)s->input, ft_tablen(s->input));
	free_t_shell(s);
	exit(EXIT_FAILURE);
}

int		execute_cmd(t_shell *s)
{
	pid_t	pid;
//	int		pipe[2];
	int		status;

	status = EXIT_FAILURE;

//	NOTE !!! -- builtin funcs must write to s->write_fd
	if ((status = try_builtin(s)) == ERR_NOTFOUND)
	{

// 	NOTE !! !! --
//	--	This function must only execute the command given.
//		It will write to the write-end of the pipe (pipe[1]), so that
//		the parent process can read from the read-end of the pipe (pipe[0]).
//	--	The parent process can then take the pipe and read pipe[0] and write
//		to a required fd. Could write to another pipe[1] from its own parent process 
//
	
		pid = fork();
		if (pid < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
		{

printf("Trying to execute '%s' with '%s' ...", s->input[0], s->input[1]); // debug

		// child only
			if (s->n_redirs) // if theres redirs, do them FIRST!
			{
				
				//	If a left redir(<) is found, read from arg defined after (<)
				//	i.e execute arg, and read its output into cmd. 					e.g	cmd < file.txt
				//																		open file.txt
				//																		read file.txt into stdin for cmd.

			}
			else if (s->n_pipes)// else if no redirs, are there pipes? If yes, use it.
			{
printf("execute_cmd() pipes -- s->write_Fd = %d\n", s->write_fd); // debug
				dup2(s->write_fd, STDOUT_FILENO);	// REDIR STDOUT to write-end of pipe
				close(s->pipes[s->pipe_i][0]);		// Not reading from pipe, only writing
				close(s->pipes[s->pipe_i][1]);		// Duplicated this fd and redirs the STDOUT to the pipe.
													// Can use STDOUT and pipe[1] interchangeably
													// closed pipe[1] as its not needed
				try_system(s);
			}
			else	// no redirs and no pipes
			{
printf("execute_cmd() -- s->write_Fd = %d\n", s->write_fd); // debug
				dup2(s->write_fd, STDOUT_FILENO);	// REDIR STDOUT to write-end of pipe
				close(s->pipes[s->pipe_i][0]);		// Not reading from pipe, only writing
				close(s->pipes[s->pipe_i][1]);		// Duplicated this fd and redirs the STDOUT to the pipe.
													// Can use STDOUT and pipe[1] interchangeably
													// closed pipe[1] as its not needed
				try_system(s);
			}


		// child has executed and written to the output fd required, whether its for a pipe, redir or screen.
		}
		// Parent only
//	Just wait for child and check its exit status.
		wait(&status);
// error checks
		if (WIFEXITED(status) && (status = WEXITSTATUS(status)) == EXIT_FAILURE)
				return (err(ERR_NOTFOUND, s->input[0]));
	}
	return (status);
}
