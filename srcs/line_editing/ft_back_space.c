/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 12:31:10 by tmack             #+#    #+#             */
/*   Updated: 2016/09/05 12:40:52 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_line_back_space(t_shell *s)
{
	int     i;
	int		j;

	if (s->curs_pos != s->str_len)
	{
		i = s->curs_pos;
		j = i;
		while (i <= s->str_len - (s->prompt_len - 2))
		{
			if (s->new_line[j - 1] == '\n')
				j++;
			s->new_line[j - 1] = s->new_line[i];
			i++;
			j++;
		}
		s->new_line[s->str_len] = '\0';
	}
	else
		s->new_line[s->curs_pos] = '\0';
	s->new_line[s->str_len - 1] = '\0';
}

void    back_shorter(t_shell *s)
{
	int     i;

	i = (s->curs_pos + s->prompt_len) - (s->width * (s->cols - 1));
	while ((i - s->width) > 0)
		i = i - s->width;
	if (((s->str_len + s->prompt_len - 1) - (s->width * (s->cols - 1))) ==
			s->width && s->curs_pos == s->str_len)
		tputs(tgetstr("do", 0), 1, ft_putchar_re);
	if ((s->curs_col != s->cols && (s->str_len + s->prompt_len - 1) -
				(s->width * (s->cols - 1)) > s->width))
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
	if (i == s->width && s->curs_pos != s->str_len)
	{
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
		i = -1;
		while (i++ < s->width)
			tputs(tgetstr("nd", 0), 1, ft_putchar_re);
	}
}

void    ft_put_curs_back(t_shell *s)
{
	int     j;
	int     i;

	i = 0;
	back_shorter(s);
	j = s->curs_pos - (s->width * (s->cols - 1));
	while (j - s->width > 0)
		j = j - s->width;
	if (j + s->prompt_len != s->width)
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	if (s->cols == 0)
		i = ft_curs_pos(s) + s->prompt_len - 1;
	else
		i = ft_curs_pos(s) - s->prompt_len + 1;
	while (i-- > 0)
		tputs(tgetstr("nd", 0), 1, ft_putchar_re);
	i = s->cols - s->curs_col;
}

void	ft_back_clear(t_shell *s)
{
	ft_put_string(s);
	ft_put_curs_back(s);
}

void    ft_backspace(t_shell *s, char *buff)
{
	if (buff[0] == 127 && s->curs_pos > 0)
	{
		ft_line_back_space(s);
		ft_nbr_cols(s);
		ft_curs_col(s);
		ft_back_clear(s);
		s->curs_pos--;
		s->str_len--;
	}
}
