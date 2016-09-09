/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 12:54:34 by tmack             #+#    #+#             */
/*   Updated: 2016/09/09 12:59:28 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    ft_cut_1(t_shell *s, char *new_line)
{
	int     i;
	int     j;
	int     k;

	k = 0;
	j = 0;
	i = 0;
	while (j < s->str_len + 1)
	{
		if (j == (s->cpy_nbr - s->a) + 1)
			while (k < s->a)
			{
				s->cpy_cut[k] = s->new_line[j];
				j++;
				k++;
			}
		new_line[i] = s->new_line[j];
		i++;
		j++;
	}
	s->cpy_nbr = 0;
}

void    ft_cut(t_shell *s, char *buff)
{
	int     i;
	char    *new_line;

	if (buff[0] == 24 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
	{
		if (s->cpy_cut != NULL)
			free(s->cpy_cut);
		s->cpy_cut = ft_strnew(s->a + 1);
		ft_bzero(s->cpy_cut, s->a + 1);
		new_line = ft_strnew(s->str_len - s->a);
		ft_bzero(new_line, s->str_len - s->a);
		ft_cut_1(s, new_line);
		free(s->new_line);
		s->new_line = ft_strdup(new_line);
		tputs(tgetstr("sc", 0), 1, ft_putchar_re);
		ft_put_string(s);
		tputs(tgetstr("rc", 0), 1, ft_putchar_re);
		i = -1;
		while (++i < s->a)
			tputs(tgetstr("le", 0), 1, ft_putchar_re);
		s->curs_pos = s->curs_pos - s->a;
		s->str_len = ft_strlen(s->new_line) + 1;
		ft_strdel(&new_line);
		s->a = 0;
	}
}
