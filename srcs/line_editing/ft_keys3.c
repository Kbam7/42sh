/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 12:58:16 by tmack             #+#    #+#             */
/*   Updated: 2016/09/11 11:47:12 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_right_word(t_shell *s, char *buff)
{
	int		i;

	i = 0;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 &&
			buff[3] == 59 && buff[4] == 50 && buff[5] == 67)
	{
		s->on = 1;
		if (s->new_line[s->curs_pos - 1] == ' ' &&
				s->curs_pos < (s->str_len - (1 + s->prompt_len)))
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

	i = 0;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 &&
			buff[3] == 59 && buff[4] == 50 && buff[5] == 68)
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
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 &&
			buff[3] == 59 && buff[4] == 50 && buff[5] == 65)
	{
		if (s->curs_pos + 1 > s->width)
		{
			tputs(tgetstr("up", 0), 1, ft_putchar_re);
			s->curs_pos = s->curs_pos - s->width;
		}
	}
}

void	ft_move_down(t_shell *s, char *buff)
{
	int		i;
	int		j;

	j = 0;
	i = s->curs_pos;
	ft_nbr_cols(s);
	ft_curs_col(s);
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 &&
			buff[3] == 59 && buff[4] == 50 && buff[5] == 66)
	{
		while (i - s->width > 0)
			i = i - s->width;
		j = s->str_len;
		while (i - s->width > 0)
			j = j - s->width;
		if (i < j && s->str_len > s->width && s->curs_col != s->cols)
		{
			tputs(tgetstr("do", 0), 1, ft_putchar_re);
			tputs(tgetstr("cr", 0), 1, ft_putchar_re);
			j = 0;
			while (j++ <= i + s->prompt_len - 1)
				tputs(tgetstr("nd", 0), 1, ft_putchar_re);
			s->curs_pos = s->curs_pos + s->width;
		}
	}
}
