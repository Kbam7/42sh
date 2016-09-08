/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 12:04:04 by tmack             #+#    #+#             */
/*   Updated: 2016/09/07 09:16:14 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_nbr_cols(t_shell *s)
{
	int		temp;
	int		i;

	i = 0;
	temp = s->str_len + s->prompt_len;
	s->width = tgetnum("co");
	while (1)
	{
		temp = temp - s->width;
		if (temp >= 0)
			i++;
		else
			break ;
	}
	s->cols = i;
}

void	ft_curs_col(t_shell *s)
{
	int		temp;
	int		i;

	i = 0;
	temp = s->curs_pos + s->prompt_len;
	while (1)
	{
		temp = temp - s->width;
		if (temp >= 0)
			i++;
		else
			break ;
	}
	s->curs_col = i;
}

int		ft_curs_pos(t_shell *s)
{
	int		temp;

	temp = s->curs_pos + s->prompt_len + 1;
	ft_nbr_cols(s);
	if (s->cols == 0)
		temp = s->curs_pos;
	else
		while (temp - s->width > 0)
			temp = temp - s->width;
	return (temp);
}

void	ft_end_right(t_shell *s, char *buff)
{
	int		i;
	int		j;

	j = -1;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 70)
	{
		ft_nbr_cols(s);
		ft_curs_col(s);
		i = s->cols - s->curs_col;
		while (i-- > 0)
			tputs(tgetstr("do", 0), 1, ft_putchar_re);
		s->curs_pos = s->str_len;
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
		if (s->cols == 0)
			i = s->prompt_len;
		else
			i = -1;
		while (++j < ft_curs_pos(s) + i)
			tputs(tgetstr("nd", 0), 1, ft_putchar_re);
	}
}

void	ft_end_left(t_shell *s, char *buff)
{
	int		j;

	j = 0;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 72)
	{
		ft_nbr_cols(s);
		ft_curs_col(s);
		j = s->curs_col;
		while (j-- > 0 && s->curs_pos != 0)
			tputs(tgetstr("up", 0), 1, ft_putchar_re);
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
		tputs(tgetstr("nd", 0), 1, ft_putchar_re);
		tputs(tgetstr("nd", 0), 1, ft_putchar_re);
		s->curs_pos = 0;
	}
}
