/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 22:05:17 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/16 12:09:09 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	*saveto_nxt_cmd(char **cmd, char **str, int strt, int len)
{
	char	*oldcmd;
	char	*tmp;

	if (*cmd == NULL)
		*cmd = ft_strsub(*str, strt, len);
	else
	{
		tmp = ft_strsub(*str, strt, len);
		oldcmd = *cmd;
		*cmd = ft_strjoinstr(oldcmd, " ", tmp);
		ft_strdel(&tmp);
		ft_strdel(&oldcmd);
	}
	// keep everything before strt
	tmp = ft_strsub(*str, 0, (ft_strlen(*str) - len));
	ft_strdel(str);
	*str = tmp;
	return(*str);
}

static char	*saveto_cmd(char **cmd, char **str, int strt, int len)
{
	char	*oldcmd;
	char	*tmp;

	if (*cmd == NULL)
		*cmd = ft_strsub(*str, strt, len);
	else
	{
		tmp = ft_strsub(*str, strt, len);
		oldcmd = *cmd;
		*cmd = ft_strjoinstr(oldcmd, " ", tmp);
		ft_strdel(&tmp);
		ft_strdel(&oldcmd);
	}
	// remove everything before strt
	tmp = ft_strsub(*str, len, (ft_strlen(*str) - len));
	ft_strdel(str);
	*str = tmp;
	return(*str);
}

static int	check_ampersand(char **str, char **cmd, t_shell *s)
{
	int amp;
	int pos;

	if (ft_strchr(ft_strchr(*str, '&') + 1, '&'))
		return (err(ERR_BAD_TOKEN, "&")); // ('&>&' || '&<&' ...)
//dprintf(2, "check_prefix() -- check_ampersand() -- Theres only one '&'\n"); // debug
	amp = get_pos(*str, '&'); // find amp ('&')
	pos = get_pos(*str, s->redir.dir); // find redir symbol
//dprintf(2, "check_prefix() -- check_ampersand() -- found positions for amp(%d) and pos(%d)\n", amp, pos); // debug
//dprintf(2, "check_prefix() -- check_ampersand() -- *str = '%s'\t*str[amp] = '%c'\t*str[amp+1] = '%c'\n", *str, (*str)[amp], (*str)[amp+1]); // debug
	if (amp < pos && (*str)[amp + 1] == '<')
	{
//dprintf(2, "check_prefix() -- check_ampersand() -- found '&<'\n"); // debug
		*str = saveto_cmd(cmd, str, 0, pos); // go to redir symbol and save everything before it as a cmd
	}
	else if (amp < pos && (*str)[amp + 1] == '>')
	{
//dprintf(2, "check_prefix() -- check_ampersand() -- found '&>'\n"); // debug
		if (amp > 0 && (*str = saveto_cmd(cmd, str, 0, amp)))  //	if theres something before '&>', save it to cmd
			amp = get_pos(*str, '&'); // find amp ('&')
		if ((*str)[amp + 2] == '>')
			amp++;
		if ((*str)[amp + 2] != '\0' && (pos = amp + 2)) 	 //	if theres something after '&>' || '&>>', save it to nxt_cmd
			*str = saveto_nxt_cmd(&s->redir.nxt_cmd, str, pos, (ft_strlen(*str) - pos));
	}
//dprintf(2, "check_prefix() -- check_ampersand() -- END\n"); // debug
	return (EXIT_SUCCESS);
}

char		*check_prefix(char **str, int pos, char **cmd, t_shell *s)
{
	int		j;


// MAKE SURE TO LEAVE FD's on both sides ATTACHED TO rdr_str.

	if (ft_strchr(*str, '&') && (check_ampersand(str, cmd, s) != EXIT_SUCCESS))
		return (NULL);
	pos = get_pos(*str, s->redir.dir);
	if (ft_isdigit((*str)[pos - 1])) // if theres a number directly before the redir symbol, leave it in the rdr_str. add to cmd anything before the number (0 -> num_strt - 1)
	{
		j = pos - 1;
		while (j > 0 && ft_isdigit((*str)[j - 1]))
			--j;
		if ( j > 0 && !ft_isdigit((*str)[j - 1])) // if theres anything before the int, save it to cmd
			*str = saveto_cmd(cmd, str, 0, j);
	}
	else if (pos > 0 && (*str)[pos - 1] != '&') // Not '&>..' and not integer, save it to cmd
		*str = saveto_cmd(cmd, str, 0, pos);
	return (*str);
}
