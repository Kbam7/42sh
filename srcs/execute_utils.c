/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 18:08:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/09 23:20:01 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	child_pipe(t_shell *s)
{
	int	i;

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
}

int		child_output_redir(char *str, t_shell *s)
{
	// execute this inside child process
	// this function must be executed just before executing the command

	//	find the type of  redir, 
	//	if theres a fd defined, output to the fd or redirect the fd depending on the reder string
	// write output to pipe[i + 1]
	int	i;

	i = 0;
	while (str[i] != '\0' && (str[i] != '>' || str[i] != '<'))
		++i;
	if (str[i] == '>')
	{
		if (i == 1 && str[i - 1] == '&')	// ('&>')
		{
			// redir STDOUT && STDERR to pipe. 
			dup2(s->redir.pipe[i + 1][1], s->redir.out_fd);
			dup2(s->redir.pipe[i + 1][1], s->redir.in_fd);
			close(s->redir.pipe[i + 1][1]);	// not needed, dupliated and redirected STDOUT to duplicate pipe
			close(s->redir.pipe[i][0]);		// not reading from current pipe
			close(s->redir.pipe[i][1]);		// not writing to current pipe
		}
		else if (i == 0)	// (' >..')
		{
			// no FD defined, redir STDOUT fd(1), to destination
			dup2(s->redir.pipe[i + 1][1], s->redir.out_fd);
			close(s->redir.pipe[i + 1][1]);
			close(s->redir.pipe[i][0]);		// not reading
			close(s->redir.pipe[i][1]);		// writing to duplicate
		}
		if (str[i + 1] == '>')	// ('>>')
		{
			//	append to output destination
			s->redir.appnd = 1;
			++i;
		}
		if (str[i + 1] == '&')	// ('>&' || '>>&')
		{
			// duplicate fd defined after '&', but before the next space.. ('2>&1') -- this will redir stderr to stdout

			if (str[i + 2] == '-' && i == 0)	// ('>&-')
				close(STDIN_FILENO);
			++i;
		}
	}
	else if (str[i] == '<')
	{
	}
	return (EXIT_SUCCESS);
}

int		parent_output_redir(char *str, t_shell *s)
{
	// execute this inside parent process after child has written to the pipe
	// this function will execute the second command and then increment s->redir.rdr_i to move to the next redir if there is one
	// The parent must now execute the second command after the redir as to complete the redir.

// NOTE !!:
//	The first command of a redir is the current index (i.e. s->redir.rdr_i ==> s->redir.cmd[i] && s->redir.rdr[i])
//	The second command that a redir executes is s->redir.cmd[i + 1].
//	 and it is ONLY A PATH TO A FILE, if its == NULL, then we ended on a redir
//	  without a cmd. 
//
//	  If does not exist, 
//	  then create it if you have the rights and write to the file.
//	  If s->redir.appnd == 1, then append to file, else truncate to zero(if it already exists),
//	  and write to it from the current pipe. (i.e. s->redir.pipe[i])

	int		i;
	int		fd;
	char	buf;

	i = 0;
	while (str[i] != '\0' && (str[i] != '>' || str[i] != '<'))
		++i;
	if (str[i] == '>')
	{
		if (i == 1 && str[i - 1] == '&')	// ('&>')
		{
			// redir STDOUT && STDERR of s->redir.cmd[i] to s->redir.cmd[i + 1]
			if (s->redir.appnd)
				if ((fd = open(s->redir.cmd[i + 1], O_CREAT | O_APPEND)) == -1)
					return (err(ERR_CREATE, s->redir.cmd[i + 1]));
			else
				if ((fd = open(s->redir.cmd[i + 1], O_CREAT | O_TRUNC)) == -1)
					return (err(ERR_CREATE, s->redir.cmd[i + 1]));
			while (read(s->redir.pipe[i + 1][0], &buf, 1) > 0)
				write(fd, &buf, 1);
			close(fd);
		}
		else if (i == 0)	// (' >..')
		{
			// no FD defined, redir STDOUT fd(1), to destination
			dup2(s->redir.pipe[i + 1][1], STDOUT_FILENO);
			close(s->redir.pipe[i + 1][1]);
			close(s->redir.pipe[i][0]);		// not reading
			close(s->redir.pipe[i][1]);		// writing to duplicate
		}

// check for file descriptors defined before/after the '>'

		if (str[i + 1] == '&')	// ('>&' || '>>&')
		{
			// duplicate fd defined after '&', but before the next space.. ('2>&1') -- this will redir stderr to stdout
			if (str[i + 2] == '-' && i == 0)	// ('>&-')
				close(STDIN_FILENO);
			++i;
		}
	}
	else if (str[i] == '<')
	{
	}
	// successfully completed the child command, the redirect and the parents path
	return (EXIT_SUCCESS);
}
