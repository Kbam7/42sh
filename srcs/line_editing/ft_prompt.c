/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 09:14:43 by kgani             #+#    #+#             */
/*   Updated: 2016/09/10 14:46:22 by kbamping         ###   ########.fr       */
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

static void	ft_assign_prompt_value(t_shell *s)
{
	char		*path;
	char		*tmp;

	path = get_path(s);
	if (s->arg_p && s->arg_u)
	{
		tmp = ft_strjoin("\033[01;33m", ft_getenv("USER", s));
		s->prompt = ft_strjoinstr(tmp, "@\033[01;0m", path);
		ft_strdel(&tmp);
	}
	else if (s->arg_p)
		s->prompt = ft_strjoin("\033[01;33m@", path);
	else if (s->arg_u)
		s->prompt = ft_strjoinstr("\033[01;33m", ft_getenv("USER", s), C_NONE);
	else
		s->prompt = ft_strnew(1);
	ft_strdel(&path);
}

static int	ft_get_prompt_len(t_shell *s)
{
	int		*filter;
	char	buf[4096];

	ft_bzero(buf, 4096);
	if ((filter = (int *)malloc(sizeof(int) * 2)) == NULL)
		return (err(ERR_MALLOC, "ft_get_prompt()"));
	if (pipe(filter) == -1)
		return (err(ERR_CREATE_PIPE, "ft_get_prompt()"));
	write(filter[1], s->prompt, ft_strlen(s->prompt));
	close(filter[1]);
	read(filter[0], buf, 4096);
	close(filter[0]);
	s->prompt_len = ft_strlen(buf);
	return (EXIT_SUCCESS);
}

void	set_prompt(t_shell *s)
{
	char		*tmp;

	if (s->prompt)
	{
		free(s->prompt);
		ft_assign_prompt_value(s);
		tmp = ft_strjoin(s->prompt, "\033[01m$>\033[0m ");
		ft_prompt_new(tmp, s);

	}
}

void	ft_prompt_print(t_shell *s)
{
	ft_putstr(s->prompt);
}

void	ft_prompt_new(char *new_prompt, t_shell *s)
{
	if (s->prompt)
		free(s->prompt);
	s->prompt = ft_strdup(new_prompt);
	ft_get_prompt_len(s);
}
