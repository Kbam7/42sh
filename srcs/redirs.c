/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/06 14:25:22 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	is_whtspc(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r')
		return (1);
	return (0);
}

void	execute_redirs(t_shell *s)
{
	// this function will call process_input() witheach redir and create pipes as needed
	t_redirs	*list;

	list = s->redirs;
	while (list)
	{
		process_output_redir();
		list = list->next;
	}

}

void	process_output_redir(char *str, t_shell *s)
{
	// this function must be executed just before executing the command
	//	this function will create the necessary redirect (pipe) for the current redir
	// try call process_input() to execute the commands after redirections are done

		// write output to pipe

				if (str[0] == '&' && str[1] == '>')	// ('&>')
				{
				// redir STDOUT && STDERR to output destination
					
				}
				if (i == 0 || is_whtspc(cmd[i - 1]))	// ('>..' || ' >')
					// no FD defined, redir STDOUT fd(1), to destination
				if (cmd[++i] == '>')	// ('>>')
				{
					//	append to output destination
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
			return (err(ERR_MALLOC, "add_redir() --"));
	}

	if (ret = execute_redirs(s) != EXIT_SUCCESS)
		return (err(ERR_NOEXEC_REDIR));
	return (ret);
}

/*
	if (ft_strchr(cmd, '>'))
	{
		// do OUTPUT REDIR '>'
		//	If a right redir(>) is found, output to arg defined after (>)
		//	i.e read from arg into stdin for cmd. 					e.g	cmd < file.txt
		//																		open file.txt
		//																		read file.txt into stdin for cmd.

	else if (ft_strchr(cmd, '<'))
	{
		// do INPUT REDIR '<'
		//	If a left redir(<) is found, read from arg defined after (<)
		//	i.e execute arg, and read its output into cmd. 					e.g	cmd < file.txt
		//																		open file.txt
		//																		read file.txt into stdin for cmd.

	}
*/
