/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 14:12:20 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 14:09:57 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_move_left(t_shell *shell, char *buff)
{
    int     i;

    i = -1;
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 68 && shell->curs_pos > 0)
			|| shell->on == 1 )
	{
        if (((shell->curs_pos + 2) % shell->width) == 0)
        {
		        tputs(tgetstr("up", 0), 1, ft_putchar_re);
            while (++i <= shell->width)
		        tputs(tgetstr("nd", 0), 1, ft_putchar_re);
	    	shell->curs_pos--;
        }
        else
        {
	    	shell->curs_pos--;
	    	tputs(tgetstr("le", 0), 1, ft_putchar_re);
        }
	}
}

void	ft_move_right(t_shell *shell, char *buff)
{
    int     i;

    i = shell->curs_pos;
	if ((buff[0] == 27 && buff[1] == 91 && buff[2] == 67 &&
			shell->curs_pos < shell->str_len) || shell-> on == 1)
	{
        if (((shell->curs_pos + 3) % shell->width) == 0)
        {
             tputs(tgetstr("do", 0), 1, ft_putchar_re);
		     tputs(tgetstr("cr", 0), 1, ft_putchar_re);
			 shell->curs_pos++;
        }
        else
        {
	    	shell->curs_pos++;
	    	tputs(tgetstr("nd", 0), 1, ft_putchar_re);
        }
	}
}

void	ft_move_cur(char *buff, t_shell *shell)
{
	ft_move_down(shell, buff);
	ft_move_up(shell, buff);
	ft_left_word(shell, buff);
	ft_right_word(shell, buff);
	ft_move_left(shell, buff);
	ft_move_right(shell, buff);
	ft_backspace(shell, buff);
	ft_history_up(shell, buff);
	ft_history_down(shell, buff);
	ft_end_right(shell, buff);
	ft_end_left(shell, buff);
	ft_enter(buff, shell);
}

void	buffer(t_shell *shell)
{
	char	*temp;

	shell->width = tgetnum("co");
    temp = (char *)malloc(sizeof(char) * 4);
	ft_bzero(temp, 4);
	read(0, temp, 4);
	/*	ft_putnbr(temp[0]);
		ft_putchar(' ');
		ft_putnbr(temp[1]);
		ft_putchar(' ');
		ft_putnbr(temp[2]);
		ft_putchar('\n');*/
	ft_move_cur(temp, shell);
		ft_print_char(temp, shell);
        free(temp);
}
