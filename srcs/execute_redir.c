/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 02:00:06 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/13 14:49:07 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		child_output_redir(char *str, t_shell *s)
{
	// execute this inside child process
	// this function must be executed just before executing the command

	//	find the type of  redir, 
	//	if theres a fd defined, output to the fd or redirect the fd depending on the reder string
	// write output to pipe[i + 1]
	int		i;
	char	*tmp;

	i = get_pos(str, '>');
	if (str[i] == '>')
	{
		s->redir.pre_fd = STDOUT_FILENO; 
		if (i == 1 && str[i - 1] == '&')	// ('&>')
		{
			// redir STDOUT && STDERR to pipe. 
//			dup2(s->redir.pipe[i + 1][1], STDOUT_FILENO);
//			dup2(s->redir.pipe[i + 1][1], STDERR_FILENO);
//			close(s->redir.pipe[i + 1][1]);	// not needed, dupliated and redirected STDOUT to duplicate pipe
			dup2(s->redir.pipe[i][1], STDOUT_FILENO);
			dup2(s->redir.pipe[i][1], STDERR_FILENO);
			close(s->redir.pipe[i][0]);		// not reading from current pipe
			close(s->redir.pipe[i][1]);		// using duped end
		}
		else if (i > 0 && ft_isdigit(str[i - 1])) // ('2>' || '43>')
		{
		// use as fd to read from, if not defined, its STDOUT
			tmp = ft_strsub(str, 0, i);
			s->redir.pre_fd = ft_atoi(tmp);
			ft_strdel(&tmp);
	//		dup2(s->redir.pipe[i + 1][1], s->redir.pre_fd);
	//		close(s->redir.pipe[i + 1][1]);	// not needed, duplicated and redirected the FD to duplicate pipe
			dup2(s->redir.pipe[i][1], s->redir.pre_fd);
			close(s->redir.pipe[i][0]);		// not reading from current pipe
			close(s->redir.pipe[i][1]);		// not writing to current pipe
		}
		else if (i == 0)	// ('>..')
		{
	//		dup2(s->redir.pipe[i + 1][1], s->redir.pre_fd);
	//		close(s->redir.pipe[i + 1][1]);
			dup2(s->redir.pipe[i][1], STDOUT_FILENO);
			close(s->redir.pipe[i][0]);		// not reading
			close(s->redir.pipe[i][1]);		// writing to duplicate
		}
		if (str[i + 1] == '>')	// ('>>')
			++i;
		if (str[i + 1] == '&')	// ('>&')
		{ // MAKE SURE TO LEAVE FD's on both sides ATTACHED TO rdr_str.
			if (str[i + 2] == '-')	// ('>&-')
				close(s->redir.pre_fd);
			else
			{ // duplicate fd defined after '&', ('2>&1') -- this will redir stderr to stdout
				tmp = ft_strsub(str, (i + 2), (ft_strlen(str) - (i + 2)));
				s->redir.post_fd = ft_atoi(tmp);
				ft_strdel(&tmp);
				dup2(s->redir.post_fd, s->redir.pre_fd);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int		parent_output_redir(char *str, t_shell *s)
{
	// execute this inside parent process after child has written to the pipe
	// The parent must now write to the path defined at s->redir.cmd[i + 1] as to complete the redir.

// NOTE !!:
//	The first command of a redir is the current index (i.e. s->redir.rdr_i ==> s->redir.cmd[i] && s->redir.rdr[i])
//	The second command that a redir executes is s->redir.cmd[i + 1].
//	 and it is ONLY A PATH TO A FILE, if its == NULL, then we ended on a redir
//	  without a cmd and an error is printed 
//
//	  If the path (cmd[i + 1]) does not exist, 
//	  then create it if you have the rights and write to the file.
//	  If s->redir.appnd > 0, then append to file, else truncate to zero(if it already exists),
//	  and write to it from the current pipe. (i.e. s->redir.pipe[i])

	int		i;
	int		pos;
	int		fd;
	char	buf;

	pos = get_pos(str, '>');
	i = s->redir.rdr_i;
	if (str[pos] == '>')
	{
		s->redir.appnd = (str[pos + 1] == '>') ? 1 : 0;
		if (pos == 1 && str[pos - 1] == '&')	// ('&>')
		{// redirected STDOUT && STDERR of s->redir.cmd[i] to pipe, write to s->redir.cmd[i + 1]
			if (s->redir.cmd[i + 1] == NULL)
				return (err(ERR_BAD_TOKEN, "newline"));
			if (s->redir.appnd)
				fd = open(s->redir.cmd[i + 1], O_CREAT | O_APPEND);
			else
				fd = open(s->redir.cmd[i + 1], O_CREAT | O_TRUNC);
			if (fd < 0)
				return (err(ERR_CREATE, s->redir.cmd[i + 1]));
			while (read(s->redir.pipe[i][0], &buf, 1) > 0)
				write(fd, &buf, 1);
			close(s->redir.pipe[i][0]);
			close(s->redir.pipe[i][1]);
			close(fd);
		}
		else if (pos > 0 && ft_isdigit(str[pos - 1])) // ('2>')
		{
		// use as fd to read from, if not defined, its STDOUT
		//	 read from pipe, into
		}
		if (pos == 0)	// ('>..')
		{
			// no FD defined, redir STDOUT fd(1), to destination
			if (s->redir.appnd)
				fd = open(s->redir.cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664); // S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
			else
				fd = open(s->redir.cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664); // S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
			if (fd < 0)
				return (err(ERR_CREATE, s->redir.cmd[i + 1]));
				
			while (read(s->redir.pipe[i][0], &buf, 1) > 0)
				write(fd, &buf, 1);
			close(s->redir.pipe[i][0]);
			close(s->redir.pipe[i][1]);
			close(fd);
		}
	}
	// successfully completed the child command, the redirect and the parents path
	return (EXIT_SUCCESS);
}

