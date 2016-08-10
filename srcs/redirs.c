/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/10 14:32:54 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	reset_and_free_vars(t_shell *s)
{
	free_tab((void **)s->redir.rdr, ft_tablen(s->redir.rdr));
	free_tab((void **)s->redir.cmd, ft_tablen(s->redir.cmd));
	s->redir.n_rdr = 0;
	s->redir.rdr_i = 0;
}


/*
** This function checks if the prefix before the redir symbols is a number.
** If it is a number, use it as the s->redir.out_fd
*/
static int	check_prefix(char *str, int start, char dir, t_shell *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[start + i] != dir && str[start + i] != '\0')
	{
		if (ft_isdigit(str[start + i]))
		{
			j = i;
			while (ft_isdigit(str[start + j]))
				++j;
			if (str[j] != dir)
			{
				// invalid command .. ('4..>' || '4..<')
				break ;
			}
			tmp = ft_strsub(str, i, (j - i));
			if (dir == '>')
				s->redir.out_fd = ft_atoi(tmp);
			else if (dir == '<')
				s->redir.in_fd = ft_atoi(tmp);
			ft_strdel(&tmp);
		}
		++i;	
	}
	return (EXIT_SUCCESS);	
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
		s->redir.rdr_i = i;
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
	reset_and_free_vars(s);
	return (ret);
}

int		process_redir(char *cmd, t_shell *s)
{

	int		i;
	int		len;
//	int		open;
	int		offset;
	char	*path;
	char	*rdr_str;

//	open = 0;
	i = 0;

	// the purpose of this loop is to store the redir string and the commands/paths
	// on either side of the redir. The function then execute the redirs, so it will
	// run until it 

	while (cmd[i] != '\0')
	{
		path = NULL;
		rdr_str = NULL;
		offset = i;
/*		
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
*/
		//	if write to file
		if (cmd[i] == '>')
		{
		// write output to pipe then write pipe to file/path
		// get redir string, and process_output_redir()

			// go to start index of rdr_string
			while (i > offset && !ft_iswhtspc(cmd[i - 1]))
			{
				--i;
				if (cmd[i] == '&' && cmd[i + 1] == '>')
					break ;

			}
			if (i > offset)	// if i > offset, then the loop above executed atleast once
							//	and there are chars before rdr_string
			{
			//	save as a command to execute.
		 		path = ft_strsub(cmd, offset, (i - offset));
			}

			len = i; // i == start index of redir_str
			// check if chars before redir are an integer, if they are then set it to s->redir.out_fd
			check_prefix(cmd, i, '>', s);

			// go to end of rdr_string. (white-space or EOL)
			while (cmd[len] != '\0' && !ft_iswhtspc(cmd[len]))
				++len;
			//	save rdr_string
			rdr_str = ft_strsub(cmd, i, len - 1);

			if (add_redir(rdr_str, path, s) == EXIT_FAILURE)
				return (err(ERR_MALLOC, "add_redir() --"));

			i = len;
		}
		else if (cmd[i] == '<')
		{
			// get stdin from cmd after '<'..

		}
		else
			++i;
	}

	// check to see if i > len. If they are equal, it means we ended on a redir. and all has been stored ( _ > )
	// if 'i' is greater, it means cmd ends with a cmd string and we must save the leftover ( __ > __ )
	if (i > len)
	{
		// save remaining chars i --> length
		path = ft_strsub(cmd, i, (ft_strlen(cmd) - i));
		if (add_redir(NULL, path, s) == EXIT_FAILURE)
			return (err(ERR_MALLOC, "add_redir()"));
	}
	return (execute_redirs(s));
}
