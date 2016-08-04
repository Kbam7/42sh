/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/04 16:11:34 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"


int	check_builtin_env_funcs(t_shell *s)
{
	char	*tmp;
	int		ret;
	

dprintf(2, "Checkin in builtin_env_funcs '%s' ...\n", s->input[0]); // debug

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

dprintf(2, "Checkin in builtin_funcs '%s' ...\n", s->input[0]); // debug

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

char	buf;							// debug
if (s->pipe_i > 0)						// debug
{
dprintf(2, "try_system() -- path exists, printing frmom pipe now. .\n----- PRINT OUTPUT -----\n\n");	// debug
	while (read(s->read_fd, &buf, 1) > 0)	// debug
		write(s->write_fd, &buf, 1);	// debug
dprintf(2, "\n----- END PRINT OUTPUT -----\ntry_system() -- printing finished. .\n");	// debug
}
		
dprintf(2, "try_system() -- path exists, executing now. .\n----- OUTPUT -----\n\n");	// debug

				if (execve(path, s->input, var) != -1)
					ft_strdel(&path);
				exit(EXIT_SUCCESS);
			}

//dprintf(2, "try_system() -- '%s' not F_OK. Doesnt exist\n", path);	// debug

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
	int		i;

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

dprintf(2, "--- CHILD PROCESS ---\nexecute_cmd() -- Trying to execute '%s' with '%s' ...\n", s->input[0], s->input[1]); // debug

		// child only
			if (s->n_redirs) // if theres redirs, do them FIRST!
			{
dprintf(2, "child -- execute_cmd() n_redirs = %d -- s->write_fd = %d\n", s->n_redirs, s->write_fd); // debug
				i = s->redir_i;
				
				//	If a left redir(<) is found, read from arg defined after (<)
				//	i.e execute arg, and read its output into cmd. 					e.g	cmd < file.txt
				//																		open file.txt
				//																		read file.txt into stdin for cmd.

			}
			else if (s->n_pipes)// else if no redirs, are there pipes? If yes, use it.
			{
				i = s->pipe_i;
dprintf(2, "child -- execute_cmd() pipes -- ORIGINAL -- s->write_fd = %d\ts->read_fd = %d\n", s->write_fd, s->read_fd); // debug

				if (i == 0) // first cmd
				{
					dup2(s->pipes[i + 1][1], STDOUT_FILENO);// REDIR STDOUT to write-end of next pipe
					close(s->pipes[i + 1][1]);				// closed pipe[1] as its not needed
					
				}
				else if (s->n_pipes == 1) // last pipe
				{
					dup2(s->pipes[i][0], STDIN_FILENO); // read from current pipe
					close(s->pipes[i][0]);				// close dup pipe read-end
				}
				else
				{
					dup2(s->pipes[i][0], STDIN_FILENO); // read from current pipe
					close(s->pipes[i][0]);				// close dup pipe read-end
					dup2(s->pipes[i + 1][1], STDOUT_FILENO);// REDIR STDOUT to write-end of next pipe
					close(s->pipes[i + 1][1]);				// closed pipe[1] as its not needed
				}
/*
				if (s->n_pipes > 1)
				{
					// DO NOT CLOSE read-end of pipe[i], its needed by the pipe ahead of it.
					dup2(s->pipes[i][1], STDOUT_FILENO);// REDIR STDOUT to write-end of pipe
					close(s->pipes[i][1]);				// closed pipe[1] as its not needed
				}
				// if after first pipe/command, then read from the pipe, else read from STDIN
				if (i > 0)
				{	
					dup2(s->pipes[i - 1][0], STDIN_FILENO);
					close(s->pipes[i - 1][0]);			// closed. Using STDIN..
				}
*/
dprintf(2, "child -- execute_cmd() pipes -- CHANGED TO -- s->write_fd = %d\ts->read_fd = %d\n", s->write_fd, s->read_fd); // debug
				try_system(s);
			}
			else	// NO redirs and NO pipes EXIST !!
			{
//dprintf(2, "execute_cmd() -- s->write_fd(OLD) = %d\n", s->write_fd); // debug
//dprintf(s->write_fd, "ptstr with s->write_fd (%d)\n", s->write_fd);	// debug
//				if (s->pipes/* || s->redirs*/) // if there are pipes or redirs, redir the STDOUT
//				{
//					dup2(s->write_fd, STDOUT_FILENO);	// REDIR STDOUT to write-end of pipe if there are
													//	else it wil be STDOUT_FILENO by default

//dprintf(2, "execute_cmd() -- s->write_fd(NEW) = %d\n", s->write_fd); // debug
//				close(s->pipes[s->pipe_i][0]);		// Not reading from pipe, only writing
			// TESTING IF PIPE[i][1] ALREADY CLOSED
//				if (close(s->pipes[s->pipe_i][1]) == 0)
//				{
					// debug
//				}// Duplicated this fd and redirs the STDOUT to the pipe.
			//	close(s->pipes[s->pipe_i][1]);		// Duplicated this fd and redirs the STDOUT to the pipe.
													// Can use STDOUT and pipe[1] interchangeably
													// closed pipe[1] as its not needed
//				}
				try_system(s);
			}


		// child has executed and written to the output fd required, whether its for a pipe, redir or screen.
		}
// Parent only
/*
// START -- do_parent()
			if (s->n_redirs) // if theres redirs, do them FIRST!
			{
		// START -- do_parent_redir()

		// END -- do_parent_redir()
			}
			else if (s->n_pipes)// else if no redirs, are there pipes? If yes, use it.
			{
		// START -- do_parent_pipe()
				i = s->pipe_i;
				// if after first pipe/command, then read from the pipe, else read from STDIN
				if (i > 0)
				{
					dup2(s->pipes[i - 1][0], s->read_fd);	// read from pipe[i - 1][0]
					close(s->pipes[i - 1][0]); // pipe read-end not used. 
				}
	if (i > 0)	// debug
		dprintf(2, "do_parent_pipe() -- These should match if theres pipes.\n"				// debug
			"If last pipe, write will be STDOUT_FILENO. IF first, read will be STDIN_FILENO\n"// debug
			"s->write_fd >%d\ts->pipe[i][1] >%d\ns->read_fd >%d\ts->pipe[i - 1][0] >%d\n",	// debug
							s->write_fd, s->pipes[i][1], s->read_fd, s->pipes[i - 1][0]); // debug
		// END -- do_parent_pipe()
			}
			else	// NO redirs and NO pipes EXIST !!
			{
		// START -- do_parent_default()

		// END -- do_parent_default()
			}
// END -- do_parent() 
*/
//	Just wait for child and check its exit status.
		wait(&status);
// error checks
		if (WIFEXITED(status) && (status = WEXITSTATUS(status)) == EXIT_FAILURE)
				return (err(ERR_NOTFOUND, s->input[0]));
	}
	return (status);
}
