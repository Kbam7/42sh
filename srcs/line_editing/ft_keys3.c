/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 12:58:16 by tmack             #+#    #+#             */
/*   Updated: 2016/08/19 12:14:53 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_right_word(t_shell *shell, char *buff)
{
	int		i;

	if (buff[0] == 50 && buff[1] == 67 && buff[2] == 0)
	{
		shell->on = 1;
		if (shell->new_line[shell->curs_pos - 1] == ' ' &&
				shell->curs_pos < (shell->str_len - 1))
			ft_move_right(shell, buff);
		i = shell->curs_pos;
		while (shell->new_line[i] && i < (shell->str_len - 1))
		{
			if (shell->new_line[i - 1] == ' ')
				break ;
			ft_move_right(shell, buff);
			i++;
		}
		shell->on = 0;
	}
}

void	ft_left_word(t_shell *shell, char *buff)
{
	int		i;

	if (buff[0] == 50 && buff[1] == 68 && buff[2] == 0)
	{
		shell->on = 1;
		if (shell->new_line[shell->curs_pos - 1] == ' ' &&
				shell->curs_pos >= 0)
			ft_move_left(shell, buff);
		i = shell->curs_pos;
		while (i > 0)
		{
			if (shell->new_line[i - 1] == ' ')
				break ;
			ft_move_left(shell, buff);
			i--;
		}
		shell->on = 0;
	}
}

void	ft_move_up(t_shell *shell, char *buff)
{
	if (buff[0] == 50 && buff[1] == 65 && buff[2] == 0)
	{
		if (shell->curs_pos > shell->width)
		{
			tputs(tgetstr("up", 0), 1, ft_putchar_re);
			shell->curs_pos = shell->curs_pos - shell->width;
		}
	}
}

void    ft_move_down(t_shell *shell, char *buff)
{
	int		i;

	i = 0;
	if (buff[0] == 50 && buff[1] == 66 && buff[2] == 0)
	{
		i = shell->str_len;
		while (i - shell->width > 0)
			i = i - shell->width;
		if ((shell->curs_pos - 1) + shell->width < shell->width + i && shell->str_len >
				shell->width)
		{
			tputs(tgetstr("do", 0), 1, ft_putchar_re);
			i = 0;
			while (i++ <= shell->curs_pos + 1)
				tputs(tgetstr("nd", 0), 1, ft_putchar_re);
			shell->curs_pos = shell->curs_pos + shell->width;
		}
	}
}
