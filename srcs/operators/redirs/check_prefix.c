/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 22:05:17 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 12:02:36 by kbamping         ###   ########.fr       */
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
	tmp = ft_strsub(*str, 0, (ft_strlen(*str) - len));
	ft_strdel(str);
	*str = tmp;
	return (*str);
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
	tmp = ft_strsub(*str, len, (ft_strlen(*str) - len));
	ft_strdel(str);
	*str = tmp;
	return (*str);
}

static int	check_ampersand(char **str, char **cmd, t_shell *s)
{
	int amp;
	int pos;

	if (ft_strchr(ft_strchr(*str, '&') + 1, '&'))
		return (err(ERR_BAD_TOKEN, "&"));
	amp = get_pos(*str, '&');
	pos = get_pos(*str, s->redir.dir);
	if (amp < pos && (*str)[amp + 1] == '<')
		*str = saveto_cmd(cmd, str, 0, pos);
	else if (amp < pos && (*str)[amp + 1] == '>')
	{
		if (amp > 0 && (*str = saveto_cmd(cmd, str, 0, amp)))
			amp = get_pos(*str, '&');
		if ((*str)[amp + 2] == '>')
			amp++;
		if ((*str)[amp + 2] != '\0' && (pos = amp + 2))
			*str = saveto_nxt_cmd(&s->redir.nxt_cmd, str, pos,
													(ft_strlen(*str) - pos));
	}
	return (EXIT_SUCCESS);
}

char		*check_prefix(char **str, int pos, char **cmd, t_shell *s)
{
	int		j;

	if (ft_strchr(*str, '&') && (check_ampersand(str, cmd, s) != EXIT_SUCCESS))
		return (NULL);
	pos = get_pos(*str, s->redir.dir);
	if (ft_isdigit((*str)[pos - 1]))
	{
		j = pos - 1;
		while (j > 0 && ft_isdigit((*str)[j - 1]))
			--j;
		if (j > 0 && !ft_isdigit((*str)[j - 1]))
			*str = saveto_cmd(cmd, str, 0, j);
	}
	else if (pos > 0 && (*str)[pos - 1] != '&')
		*str = saveto_cmd(cmd, str, 0, pos);
	return (*str);
}
