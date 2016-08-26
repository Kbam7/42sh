/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 14:12:20 by tmack             #+#    #+#             */
/*   Updated: 2016/08/25 09:16:35 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_move_left(t_shell *s, char *buff)
{
    int     i;

    i = -1;
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 68 && s->curs_pos > 0)
			|| s->on == 1 )
	{
        if (((s->curs_pos + 2) % s->width) == 0)
        {
		        tputs(tgetstr("up", 0), 1, ft_putchar_re);
            while (++i <= s->width)
		        tputs(tgetstr("nd", 0), 1, ft_putchar_re);
	    	s->curs_pos--;
        }
        else
        {
	    	s->curs_pos--;
	    	tputs(tgetstr("le", 0), 1, ft_putchar_re);
        }
	}
}

void	ft_move_right(t_shell *s, char *buff)
{
//    int     i;

//    i = s->curs_pos;
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 67 &&
			s->curs_pos < s->str_len) || s-> on == 1)
	{
        if (((s->curs_pos + 3) % s->width) == 0)
        {
             tputs(tgetstr("do", 0), 1, ft_putchar_re);
		     tputs(tgetstr("cr", 0), 1, ft_putchar_re);
			 s->curs_pos++;
        }
        else
        {
	    	s->curs_pos++;
	    	tputs(tgetstr("nd", 0), 1, ft_putchar_re);
        }
	}
}

void	ft_move_cur(char *buff, t_shell *s)
{
	ft_move_down(s, buff);
	ft_move_up(s, buff);
	ft_left_word(s, buff);
	ft_right_word(s, buff);
	ft_move_left(s, buff);
	ft_move_right(s, buff);
	ft_backspace(s, buff);
	ft_history_up(s, buff);
	ft_history_down(s, buff);
	ft_end_right(s, buff);
	ft_end_left(s, buff);
	ft_enter(buff, s);
}

void	buffer(t_shell *s)
{
	char	*temp;

	s->width = tgetnum("co");
    temp = (char *)malloc(sizeof(char) * 4);
	ft_bzero(temp, 4);
	read(0, temp, 4);
	/*	ft_putnbr(temp[0]);
		ft_putchar(' ');
		ft_putnbr(temp[1]);
		ft_putchar(' ');
		ft_putnbr(temp[2]);
		ft_putchar('\n');*/
	ft_move_cur(temp, s);
	ft_print_char(temp, s);
	free(temp);
}
