/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 16:02:44 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/12 00:33:45 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	get_pos(char *str, char ch)
{
	int	pos;

	pos = 0;
	while (str[pos] != '\0')
	{
		if (str[pos] == ch)
			return (pos);
		++pos;
	}
	return (-1);
}

static char	*saveto_cmd(char **cmd, char *str, int, strt, int len)
{
	char	*oldcmd;

	if (*cmd == NULL)
		*cmd = ft_strsub(str, strt, len);
	else
	{
		tmp = ft_strsub(str, strt, len);
		oldcmd = *cmd;
		*cmd = ft_strjoinstr(oldcmd, " ", tmp);
		ft_strdel(&tmp);
		ft_strdel(&oldcmd);
	}
	// remove everything before
	tmp = ft_strsub(str, len, (ft_strlen(str) - len);
	ft_strdel(&str);
	str = tmp;
	return(str);
}

static int	check_ampersand(char **str, char **cmd, t_shell *s)
{
	int amp;
	int pos;

	if (ft_strchr(ft_strchr(*str, '&'), '&'))
		return (err(ERR_DBL_AMP, "")); // ('&>&' || '&<&')
	amp = get_pos(str, '&'); // find amp ('&')
	pos = get_pos(str, s->redir.dir); // find redir symbol
	if (amp < pos && *str[amp + 1] != '>')
		*str = saveto_cmd(cmd, *str, 0, pos); // go to redir symbol and save everything before it as a cmd
	else if (amp < pos && *str[amp + 1] == '>' && amp > 0) // else if theres something before '&>', save it to cmd
		*str = saveto_cmd(cmd, *str, 0, amp);
	return (EXIT_SUCCESS);
}

static char	*check_prefix(char *str, int pos, char **cmd, t_shell *s)
{
	int		j;
	char	*tmp;
	char	*oldcmd;

	if (ft_strchr(str, '&') && (check_ampersand(&str, cmd) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	pos = get_pos(str, s->redir.dir);
	if (ft_isdigit(str[pos - 1])) // if theres a number, save to pre_fd
	{
		j = pos - 1;
		while (j > 0 && ft_isdigit(str[j - 1]))
			--j;
		if ( j > 0 && !ft_isdigit(str[j - 1])) // if theres anything before the int, join everything up till pos to the end of *cmd.
			str = saveto_cmd(cmd, str, 0, pos);
/*		else
		{ // SAVE THIS FOR FOR THE CHILD to set before execution.
			tmp = ft_strsub(str, j, (pos - j));
			s->redir.pre_fd = ft_atoi(tmp);
			ft_strdel(&tmp);
*/		}
	}
	else if (pos > 0 && str[pos - 1] != '&') // Not '&' and not integer, save it to cmd
		str = saveto_cmd(cmd, str, 0, pos);
	return (str);
}

static char	*check_postfix(char *str, int pos)
{
	int		len;
	char	*tmp;

// Will not have anything before rdr_str.
	if (str[pos + 1] == dir)
	{
		if (s->redir.dir == '>') //	if ('>>'), append
			// append
		else if (s->redir.dir == '<') //	else its ('<<'), which is a here-doc/here-string
			// here-doc
		++pos;
	}
	if (str[pos + 1] == '&')
	{
		if (str[0] == '&')
			return (EXIT_FAILURE); // ('&>&' || '&<&')

		if (ft_isdigit(str[pos + 2]))
			// cycle to end of int and sace rest as s->redir.next_cmd
			//	s->redir.nxt_cmd will be joined to begining of cmd of next iteration

		// if theres a number after '&', duplicate in the child process not here, 
		//	save the number to s->redir.post_fd

		// SAVE THIS FOR THE CHILD!! -- If you close STDOUT in the parent, youre screwed!
/*		if (str[pos + 2] == '-')
		{
				//	close s->redir.pre_fd
				//	if pre_fd < 0, close STDOUT_FILENO
		}
		else
		{
		//	duplicate fd defined after '&'
		}
*/
	}
	else if ()
	return (str);
}

/*
** This function checks if there are chars before or after the redir symbol.
*/
char		*analyze_redir(char *str, char dir, char **cmd, t_shell *s)
{
	int	pos;

	s->redir.dir = dir;
	pos = 0;
	while (str[pos] != dir && str[pos] != '\0')
		++pos;
	if (str[pos] == '\0') // no redir symbol
		return (str);
	if (pos > 0)
		str = check_prefix(str, pos, cmd);
	pos = 0;
	while (str[pos] != dir && str[pos] != '\0')
		++pos;
	if (str[pos] == '\0') // no redir symbol
		return (str);
	if (str[pos + 1] != '\0')
		str = check_postfix(str, pos, cmd);
	return (str);
}
