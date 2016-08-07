/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/06 20:34:13 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	is_whtspc(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r')
		return (1);
	return (0);
}

static int	execute_redirs(t_shell *s)
{
	// this function will call process_input() witheach redir and create pipes as needed
	int	i;
	int	ret;

	i = 0;
	// cycle through redirects
	while (i < s->redir.n_rdr)
	{
	// check what type of redir is at s->redir.rdr[i], output_redir() OR input_redir()
	//	execute when the redirects are done.

		if (ft_strchr(s->redir.rdr[i], '>'))
		{
			s->redir.dir = '>';
			ret = process_input(s->redir.cmd[i], s);
	//		ret = output_redir(s->redir.rdr[i], s);
		}
		else if (ft_strchr(s->redir.rdr[i], '<'))
		{
			s->redir.dir = '<';
			ret = process_input(s->redir.cmd[i], s);
	//		ret = input_redir(s->redir.rdr[i], s);
		}
		if ((ret != EXIT_SUCCESS)
			break ;
		++i;
	}
	return (ret);
}

int		process_redir(char *cmd, t_shell *s)
{

	int		i;
	int		ret;
	int		open;
	int		offset;
	char	*path;
	char	*rdr_str;

	open = 0;
	ret = EXIT_FAILURE;
	i = 0;
	while (cmd[i] != '\0')
	{
		path = NULL;
		rdr_str = NULL;
		offset = i;
		// if quote, cycle to end quote
		if (cmd[i] == '"')
		{
			++open;
			while (open && cmd[i] != '\0')
			{
				++i;
				if (cmd[i] == '"')
					--open;
			}
			if (cmd[i] == '"')
				++i;
		}
		//	if write to file
		if (cmd[i] == '>')
		{
		// write output to pipe
		//	write pipe to file/path


		// get redir string, and process_output_redir()

			// go to start index of rdr_string
			while (i > offset && !is_whtspc(cmd[i - 1]))
			{
				--i;
				if (cmd[i] == '&' && cmd[i + 1] == '>')
					break ;
			}
			if (i > offset)	// are there chars before rdr_string
			{
			//	save as a path, if path exists, execute it.
			//					else create path and write to it--
		 		path = ft_strsub(cmd, offset, (i - offset));
			}

			len = i; // i == start index of redir_str

			// go to end of rdr_string. (white-space or EOL)
			while (cmd[len] != '\0' && !is_whtspc(cmd[len]))
				++len;
			//	save rdr_string -- check rdr string for two ampersands  (2x '&')
			rdr_str = ft_strsub(cmd, i, len - 1);

			if (add_redir(&s->redirs, rdr_str, path) == EXIT_FAILURE)
				return (err(ERR_MALLOC, "add_redir() --"));

			i = len;
		}
		else if (cmd[i] = '<')
		{
			// get stdin from cmd after '<'..

			++i;
		}
		else
			++i;
	}

	// check to see if i == ft_strlen(cmd). If they match, it means we ended on a redir. and all has been stored ( _ > )
	// if they dont match, it means cmd ends with a cmd string and we must save the leftover ( __ > __ )
	if (i < ft_strlen(cmd))
	{
		// save remaining chars i --> length
		path = ft_strsub(cmd, i, (ft_strlen(cmd) - i));
		if (add_redir(&s->redirs, NULL, path) == EXIT_FAILURE)
			return (err(ERR_MALLOC, "add_redir()"));
	}
	return (execute_redirs(s));
}

/* START -- execute_utils.c */

int		child_output_redir(char *str, t_shell *s)
{
	// execute this inside child process
	// this function must be executed just before executing the command
	//	this function will create the necessary redirect (pipe) for the current redir

		// write output to pipe
		

				if (str[0] == '&' && str[1] == '>')	// ('&>')
				{
				// redir STDOUT && STDERR of s->redir.cmd[i] to s->redir.cmd[i + 1]
					dup2(s->redir.pipes[i + 1][1], STDOUT_FILENO);
					dup2(s->redir.pipes[i + 1][1], STDERR_FILENO);
					close(s->redir.pipes[i + 1][1]);	// not needed, dupliated and redirected STDOUT to duplicate pipe
					close(s->redir.pipes[i][0]);		// not writing to current pipe
					close(s->redir.pipes[i][1]);		// not reading from current pipe
				}
				if (i == 0 || is_whtspc(cmd[i - 1]))	// ('>..' || ' >')
				{
					// no FD defined, redir STDOUT fd(1), to destination
					dup2(s->redir.pipes[i + 1][1], STDOUT_FILENO);
					close(s->redir.pipes[i + 1][1]);

				}
				if (cmd[++i] == '>')	// ('>>')
				{
					//	append to output destination
					//	s->redir.rdr_i + 1
					++i;
				}
				if (cmd[i] == '&')	// ('>&')
				{
					// ampersand
					++i;
				}
				if (cmd[i])
				while (cmd[i] != '\0' && is_whtspc(cmd[i]))	//	(> ..)
					++i;
				len = i;
				while (cmd[len] != '\0' && !is_whtspc(cmd[len]))// read chars from space to space to
					++len;										// form a word/path to a file or command..
				if (len > i)						// word found
					word = ft_strsub(cmd, i, len);	// get word
				//	WHAT TO DO WITH 'word' ???


}

/* END -- execute_utils.c */
