/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_postfix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/12 22:08:50 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 12:04:57 by kbamping         ###   ########.fr       */
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
	tmp = ft_strsub(*str, 0, strt);
	ft_strdel(str);
	*str = tmp;
	return (*str);
}

char		*check_postfix(char **str, int pos, t_shell *s)
{
	int		len;

	if (pos > 0 && (*str)[pos - 1] == s->redir.dir && (*str)[pos + 1] == '&')
		return ((err(ERR_BAD_TOKEN, "&")) ? NULL : NULL);
	if ((*str)[pos + 1] == '&')
	{
		if ((*str)[0] == '&')
			return ((err(ERR_BAD_TOKEN, "&")) ? NULL : NULL);
		if ((*str)[pos + 2] == '\0')
			return ((err(ERR_BAD_TOKEN, "newline")) ? NULL : NULL);
		if ((*str)[pos + 2] == '-')
			pos = pos + 2;
		else if (ft_isdigit((*str)[pos + 2]))
		{
			len = pos + 2;
			while (ft_isdigit((*str)[len]))
				++len;
			pos = ((*str)[len] == '\0') ? len : (pos + 2);
		}
		else
			pos = pos + 2;
	}
	if ((*str)[pos] != '\0' && (*str)[pos + 1] != '\0' && ++pos)
		saveto_nxt_cmd(&s->redir.nxt_cmd, str, pos, (ft_strlen(*str) - (pos)));
	return (*str);
}
