/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/06 03:17:39 by kbamping         ###   ########.fr       */
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

int	try_builtin(t_shell *s)
{
	int	ret;

//dprintf(2, "Checkin in builtin_funcs '%s' ...\n", s->input[0]); // debug

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

//	Prints from pipe
/*		
char	buf;							// debug
if (s->pipe.pipe_i > 0)						// debug
{
dprintf(2, "try_system() -- path exists, reading from pipe[i][0] now. .\n" // debug
			"----- PRINT OUTPUT -- to STDOUT -----\n\n");	// debug
	while (read(s->pipe.pipes[s->pipe.pipe_i][0], &buf, 1) > 0)	// debug
	{
		ft_putstr_fd(" >", 2);
		write(2, &buf, 1);	// debug
	}
dprintf(2, "\n----- END PRINT OUTPUT -----\ntry_system() -- printing finished. .\n");	// debug
}
fflush(stderr);
dprintf(2, "try_system() -- path exists, executing now. .\n----- OUTPUT -----\n\n");	// debuig
fflush(stdout);

//	(void)var;// debug
*/
				if (execve(path, s->input, var) != -1)
				{
					ft_strdel(&path);
					free_t_shell(s);
				}
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
	int		status;
	int		i;

	status = EXIT_FAILURE;

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
			if (s->redir->n_rdr) // if theres redirs, do them FIRST!
			{
//dprintf(2, "child -- execute_cmd() n_redirs = %d -- s->write_fd = %d\n", s->n_redirs, s->write_fd); // debug
				i = s->redir_i;
				
				//	If a left redir(<) is found, read from arg defined after (<)
				//	i.e execute arg, and read its output into cmd. 					e.g	cmd < file.txt
				//																		open file.txt
				//																		read file.txt into stdin for cmd.

			}
			else if (s->pipe.n_pipes)// else if no redirs, are there pipes? If yes, use it.
			{
				i = s->pipe.pipe_i;
				if (i == 0) // first cmd
				{
//		dprintf(2, "execute_cmd() -- child -- first cmd (i = 0)\n"); // debug
		//dprintf(2, "STDOUT now goes to s->pipe.pipes[i + 1][1]\n");		// debug
					dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
					close(s->pipe.pipes[i][0]);						// close STDOUT and write to pipe[i + 1]
					close(s->pipe.pipes[i][1]);						// close STDOUT and write to pipe[i + 1]

//		dprintf(2, "execute_cmd() -- --- STDOUT closed, OUTPUT goes to s->pipe.pipes[i + 1][1]\n");		// debug
//		dprintf(2, "execute_cmd() -- --- STDIN open, s->pipe.pipes[i][0] closed  -- Not reading from first pipe\n");		// debug
//		dprintf(2, "execute_cmd() -- --- s->pipe.pipes[i][1] closed  -- Not writing to first pipe\n");		// debug
				}
				else if (s->pipe.n_pipes == 1) // last pipe
				{

//		dprintf(2, "execute_cmd() -- child -- Last cmd (s->pipe.n_pipes == 1)\n"); // debug
					dup2(s->pipe.pipes[i][0], STDIN_FILENO); // read from current pipe
					close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
					close(s->pipe.pipes[i][1]);	// close last write-end, STDOUT used
	//	dprintf(2, "execute_cmd() -- STDIN closed,  input is from s->pipe.pipes[i][0]\n");		// debug
	//	dprintf(2, "execute_cmd() -- STDOUT open, writing to screen\n");		// debug
	//	dprintf(2, "execute_cmd() -- s->pipe.pipes[i][1] -- last write-end closed, writing to screen\n");		// debug
				}
				else
				{
//		dprintf(2, "execute_cmd() -- child --  middle cmd -- pipes[%d]\n", i); // debug
					close(s->pipe.pipes[i][1]);	// close this pipe, writing to next pipe
					dup2(s->pipe.pipes[i][0], STDIN_FILENO); // read from current pipe
					close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
					dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
//		dprintf(2, "execute_cmd() -- STDIN closed, reading from s->pipe.pipes[i][0]\n");		// debug
//		dprintf(2, "execute_cmd() -- STDOUT closed, writing to s->pipe.pipes[i + 1][1]\n");		// debug
				}
				try_system(s);
			}
			else	// NO redirs and NO pipes EXIST !!
			{
				try_system(s);
			}
		// child has executed and written to the output fd required, whether its for a pipe, redir or screen.
		}
		
// -----   Parent only   ------

		if (s->n_redirs) // if theres redirs, do them FIRST!
		{
			// nothing yet
		}
		else if (s->pipe.n_pipes)// else if no redirs, are there pipes? If yes, use it.
		{
			i = s->pipe.pipe_i;
			if (i == 0) // first cmd
			{
//			dprintf(2, "execute_cmd() -- parent -- first cmd (i = 0)\n"); // debug
					close(s->pipe.pipes[i][0]);						// close pipe[0], not reading from first pipe
					close(s->pipe.pipes[i][1]);						// close pipe[1], not writing to first pipe
			}
			else if (s->pipe.n_pipes == 1) // last pipe
			{
//			dprintf(2, "execute_cmd() -- Parent -- Last cmd (s->pipe.n_pipes == 1)\n"); // debug
					close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
					close(s->pipe.pipes[i][1]);	// close last write-end, STDOUT used
			}
			else
			{
//			dprintf(2, "execute_cmd() -- parent -- middle cmd -- \n"); // debug
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
