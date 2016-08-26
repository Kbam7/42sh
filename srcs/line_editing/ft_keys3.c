/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 12:58:16 by tmack             #+#    #+#             */
/*   Updated: 2016/08/25 08:16:25 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_right_word(t_shell *s, char *buff)
{
	int		i;

	if (buff[0] == 50 && buff[1] == 67 && buff[2] == 0)
	{
		s->on = 1;
		if (s->new_line[s->curs_pos - 1] == ' ' &&
				s->curs_pos < (s->str_len - 1))
			ft_move_right(s, buff);
		i = s->curs_pos;
		while (s->new_line[i] && i < (s->str_len - 1))
		{
			if (s->new_line[i - 1] == ' ')
				break ;
			ft_move_right(s, buff);
			i++;
		}
		s->on = 0;
	}
}

void	ft_left_word(t_shell *s, char *buff)
{
	int		i;

	if (buff[0] == 50 && buff[1] == 68 && buff[2] == 0)
	{
		s->on = 1;
		if (s->new_line[s->curs_pos - 1] == ' ' &&
				s->curs_pos >= 0)
			ft_move_left(s, buff);
		i = s->curs_pos;
		while (i > 0)
		{
			if (s->new_line[i - 1] == ' ')
				break ;
			ft_move_left(s, buff);
			i--;
		}
		s->on = 0;
	}
}

void	ft_move_up(t_shell *s, char *buff)
{
	if (buff[0] == 50 && buff[1] == 65 && buff[2] == 0)
	{
		if (s->curs_pos > s->width)
		{
			tputs(tgetstr("up", 0), 1, ft_putchar_re);
			s->curs_pos = s->curs_pos - s->width;
		}
	}
}

void    ft_move_down(t_shell *s, char *buff)
{
	int		i;

	i = 0;
	if (buff[0] == 50 && buff[1] == 66 && buff[2] == 0)
	{
		i = s->str_len;
		while (i - s->width > 0)
			i = i - s->width;
		if ((s->curs_pos - 1) + s->width < s->width + i && s->str_len >
				s->width)
		{
			tputs(tgetstr("do", 0), 1, ft_putchar_re);
			i = 0;
			while (i++ <= s->curs_pos + 1)
				tputs(tgetstr("nd", 0), 1, ft_putchar_re);
			s->curs_pos = s->curs_pos + s->width;
		}
	}
}
