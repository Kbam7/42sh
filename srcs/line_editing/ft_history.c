/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 09:33:16 by tmack             #+#    #+#             */
/*   Updated: 2016/08/25 08:20:13 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    ft_new_history(t_shell *s)
{
   s->history[s->h_index] = ft_strdup(s->new_line);
}

void    ft_history_up(t_shell *s, char *buff)
{
	int     i;

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65 &&
			s->h_pos < s->h_index)
	{
		while (s->curs_pos-- > 0)
			tputs(tgetstr("le", 0), 1, ft_putchar_re);
		tputs(tgetstr("ce", 0), 1, ft_putchar_re);
		s->h_pos++;
		i = s->h_index - s->h_pos;
		if (s->new_line != NULL)
			free(s->new_line);
		s->new_line = ft_strdup(s->history[i]);
		ft_putstr(s->new_line);
		s->curs_pos = ft_strlen(s->new_line);
		s->str_len = ft_strlen(s->new_line);
	}
}

void    ft_history_down(t_shell *s, char *buff)
{
	int     i;

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66 && s->h_pos > 1)
	{
		while (s->curs_pos-- > 0)
			tputs(tgetstr("le", 0), 1, ft_putchar_re);
		tputs(tgetstr("ce", 0), 1, ft_putchar_re);
		s->h_pos--;
		i = s->h_index - s->h_pos;
		if (s->new_line != NULL)
			free(s->new_line);
		s->new_line = s->history[i];
		ft_putstr(s->new_line);
		s->curs_pos = ft_strlen(s->new_line);
		s->str_len = ft_strlen(s->new_line);
	}
}
