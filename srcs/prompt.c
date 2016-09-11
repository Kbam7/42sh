/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 17:04:45 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	*get_path(t_shell *s)
{
	char	*path;
	int		len;

	s->cwd = ft_getenv("PWD", s);
	len = ft_strlen(ft_getenv("HOME", s));
	if (ft_strncmp(s->cwd, ft_getenv("HOME", s), len) == 0)
	{
		path = ft_strstr(s->cwd, ft_getenv("HOME", s));
		path = ft_strjoinstr("\033[01;34m~", path + len, C_NONE);
	}
	else
		path = ft_strjoinstr("\033[01;34m", s->cwd, C_NONE);
	return (path);
}

static void	ft_get_user(t_shell *s, char **tmp)
{
	*tmp = get_path(s);
	s->prompt = ft_strjoinstr(ft_getenv("USER", s), "@", *tmp);
	ft_strdel(tmp);
}

void		set_prompt(t_shell *s)
{
	char		*tmp;
	static int	count = 1;

	if (s->prompt && (count == 1 || s->arg_p))
	{
		free(s->prompt);
		if (s->arg_p && s->arg_u)
			ft_get_user(s, &tmp);
		else if (s->arg_p)
		{
			tmp = get_path(s);
			s->prompt = ft_strjoin("@", tmp);
			ft_strdel(&tmp);
		}
		else if (s->arg_u)
			s->prompt = ft_strjoin(ft_getenv("USER", s), C_NONE);
		else
			s->prompt = ft_strnew(1);
		tmp = ft_strjoin(s->prompt, "\033[01m $> \033[0m");
		free(s->prompt);
		s->prompt = tmp;
	}
	++count;
}
