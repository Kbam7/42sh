/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/08 21:42:33 by kbamping         ###   ########.fr       */
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
	int	i;
	int	ret;
	// this function will call process_input() witheach redir and create pipes as needed

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
		if (ret != EXIT_SUCCESS)
			break ;
		++i;
	}
	return (ret);
}

int		process_redir(char *cmd, t_shell *s)
{

	int		i;
	int		len;
	int		open;
	int		offset;
	char	*path;
	char	*rdr_str;

	open = 0;
	i = 0;

	// the purpose of this loop is to store the redir string and the cammonds/paths
	// on either side of the redir
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
		// write output to pipe then write pipe to file/path
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

			if (add_redir(rdr_str, path, s) == EXIT_FAILURE)
				return (err(ERR_MALLOC, "add_redir() --"));

			i = len;
		}
		else if (cmd[i] == '<')
		{
			// get stdin from cmd after '<'..

			++i;
		}
		else
			++i;
	}

	// check to see if i == ft_strlen(cmd). If they match, it means we ended on a redir. and all has been stored ( _ > )
	// if they dont match, it means cmd ends with a cmd string and we must save the leftover ( __ > __ )
	if (i < (int)ft_strlen(cmd))
	{
		// save remaining chars i --> length
		path = ft_strsub(cmd, i, (ft_strlen(cmd) - i));
		if (add_redir(NULL, path, s) == EXIT_FAILURE)
			return (err(ERR_MALLOC, "add_redir()"));
	}
	return (execute_redirs(s));
}
