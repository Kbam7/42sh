/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_highlight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 12:57:30 by tmack             #+#    #+#             */
/*   Updated: 2016/09/09 13:03:57 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_put_string1(t_shell *s)
{
	int		j;
	int		i;

	i = -1;
	j = 0;
	while (++i < s->curs_col)
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	tputs(tgetstr("cd", 0), 1, ft_putchar_re);
	ft_prompt_print(s);
	i = 0;
	while (s->new_line[i])
	{
		if (i > (s->cpy_nbr - s->a) && i <= s->cpy_nbr)
		{
			tputs(tgetstr("so", 0), 1, ft_putchar_re);
			ft_putchar(s->new_line[i]);
			tputs(tgetstr("se", 0), 1, ft_putchar_re);
			j++;
			i++;
			continue ;
		}
		ft_putchar(s->new_line[i]);
		i++;
	}
}

void	ft_high_right(t_shell *s, char *buff)
{
	if (buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 67)
	{
		s->cpy_nbr = s->curs_pos;
		s->a++;
		s->on = 1;
		ft_move_right(s, "A");
		s->on = 0;
		tputs(tgetstr("sc", 0), 1, ft_putchar_re);
		ft_put_string1(s);
		tputs(tgetstr("rc", 0), 1, ft_putchar_re);
	}
}

