/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_postfix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 22:08:50 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/13 02:18:18 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

/*
**
**	Make sure everything here looks at chars AFTER the redir symbol
**
*/

char		*check_postfix(char *str, int pos, t_shell *s)
{
	int		len;

// Will not have anything before rdr_str except '&' or a fd
	if (str[pos - 1] == s->redir.dir) // ('&>>..' || '>>..' || '<<..')
		if (s->redir.dir == '<') //	else its ('<<'), which is a here-doc/here-string
			ft_putstr_fd("heredoc\n", 2);// here-doc
	if (str[pos + 1] == '&')
	{
		if (str[0] == '&') // checking if theres already a '&'
			return ((err(ERR_BAD_TOKEN, "&")) ? NULL : NULL);
		if (str[pos + 2] == '\0') // error, nothing after '&'
			return ((err(ERR_BAD_TOKEN, "newline")) ? NULL : NULL);
		if (str[pos + 2] == '-')
			pos = pos + 2;
		else if (ft_isdigit(str[pos + 2]))
		{
			len = pos + 2;
			while (ft_isdigit(str[len])) // cycle to end of int
				++len;
			if (str[len] != '\0')
			{//	save everything after the '&' as s->redir.next_cmd. Even the int part. If the int isnt all the way to the end of the str, then use as cmd.
				len = pos + 2;
				s->redir.nxt_cmd = ft_strsub(str, len, (ft_strlen(str) - len));
			}
			// Left int in the rdr_str
		}
		else	// No digits or '-' after '&'
		{
			len = pos + 2;
			s->redir.nxt_cmd = ft_strsub(str, len, (ft_strlen(str) - len));
		}
	}
	else
		s->redir.nxt_cmd = ft_strsub(str, pos + 1, (ft_strlen(str) - pos + 1));
	return (str);
}
