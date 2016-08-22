/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 09:33:16 by tmack             #+#    #+#             */
/*   Updated: 2016/08/19 13:10:13 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    ft_new_history(t_shell *shell)
{
   shell->history[shell->h_index] = ft_strnew(shell->str_len + 1);
   ft_bzero(shell->history[shell->h_index], shell->str_len + 1);
   shell->history[shell->h_index] = ft_strcpy(shell->history[shell->h_index],
           shell->new_line);
}

void    ft_history_up(t_shell *shell, char *buff)
{
	int     i;

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65 &&
			shell->h_pos < shell->h_index)
	{
		while (shell->curs_pos-- > 0)
			tputs(tgetstr("le", 0), 1, ft_putchar_re);
		tputs(tgetstr("ce", 0), 1, ft_putchar_re);
		shell->h_pos++;
		i = shell->h_index - shell->h_pos;
		shell->new_line = shell->history[i];
		ft_putstr(shell->new_line);
		shell->curs_pos = ft_strlen(shell->new_line);
		shell->str_len = ft_strlen(shell->new_line);
	}
}

void    ft_history_down(t_shell *shell, char *buff)
{
	int     i;

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66 && shell->h_pos > 1)
	{
		while (shell->curs_pos-- > 0)
			tputs(tgetstr("le", 0), 1, ft_putchar_re);
		tputs(tgetstr("ce", 0), 1, ft_putchar_re);
		shell->h_pos--;
		i = shell->h_index - shell->h_pos;
		shell->new_line = shell->history[i];
		ft_putstr(shell->new_line);
		shell->curs_pos = ft_strlen(shell->new_line);
		shell->str_len = ft_strlen(shell->new_line);
	}
}
