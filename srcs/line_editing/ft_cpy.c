/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 09:29:32 by tmack             #+#    #+#             */
/*   Updated: 2016/09/06 17:12:53 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"


void    ft_put_string1(t_shell *s)
{
	int     i;

	i = 0;
	while (i < s->curs_col)
	{
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
		i++;
	}
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	tputs(tgetstr("cd", 0), 1, ft_putchar_re);
	ft_prompt_print(s);
}

void	ft_high_right(t_shell *s, char *buff)
{
	int		i;
	int		j;

	i = 0;
	if (buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 67)
	{
		s->high[s->a] = ft_itoa(s->curs_pos);
		s->high[s->a + 1] = NULL;
		s->a++;
		s->on = 1;
		ft_move_right(s, "A");
		s->on = 0;
		j = 0;
		tputs(tgetstr("sc", 0), 1, ft_putchar_re);
		ft_put_string1(s);
			j = 0;
		while (s->new_line[i])
		{
			if (s->high[j] && i == ft_atoi(s->high[j]))
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
		tputs(tgetstr("se", 0), 1, ft_putchar_re);
		tputs(tgetstr("rc", 0), 1, ft_putchar_re);
	}
}

void	ft_high_left(t_shell *s, char *buff)
{
	if (buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 68)
	{
		//	tputs(tgetstr("so", 0), 1, ft_putchar_re);
		s->on = 1;
		ft_move_left(s, "A");
		s->on = 0;
		//		tputs(tgetstr("se", 0), 1, ft_putchar_re);
	}

}
