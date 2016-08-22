/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 12:04:04 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 15:38:06 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_nbr_cols(t_shell *shell)
{
	int		temp;
	int		i;

	i = 0; 
	temp = shell->str_len + 2;
	shell->width = tgetnum("co");
	while (1)
	{
		temp = temp - shell->width;
		if (temp  >= 0)
			i++;
		else
			break ;
	}
	shell->cols = i;
}

void	ft_curs_col(t_shell *shell)
{
	int		temp;
	int		i;

	i = 0;
	temp = shell->curs_pos + 2;
	while (1)
	{
		temp = temp - shell->width;
		if (temp >= 0)
			i++;
		else
			break ;
	}
	shell->curs_col = i;
}

int		ft_curs_pos(t_shell *shell)
{
	int		temp;

	temp = shell->curs_pos + 3;
	ft_nbr_cols(shell);
	if (shell->cols == 0)
		temp = shell->curs_pos;
	else
		while (temp - shell->width > 0)
			temp = temp - shell->width;
	return (temp);
}

void	ft_end_right(t_shell *shell, char *buff)
{
	int		i;
	int		j;

	j = -1;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 70)
	{ 
		ft_nbr_cols(shell);
		ft_curs_col(shell);
		i = shell->cols - shell->curs_col;
		while (i-- > 0)
			tputs(tgetstr("do", 0), 1, ft_putchar_re);
		shell->curs_pos = shell->str_len;
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
		if (shell->cols == 0)
			i = 2;
		else
			i = -1;
		while (++j < ft_curs_pos(shell) + i)
			tputs(tgetstr("nd", 0), 1, ft_putchar_re);
	}
}

void	ft_end_left(t_shell *shell, char *buff)
{
	int		j;

	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 72)
	{
		ft_nbr_cols(shell);
		ft_curs_col(shell);
		j = shell->curs_col;
		while (j-- > 0 && shell->curs_pos != 0)
			tputs(tgetstr("up", 0), 1, ft_putchar_re);
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
		tputs(tgetstr("nd", 0), 1, ft_putchar_re);
		tputs(tgetstr("nd", 0), 1, ft_putchar_re);
		shell->curs_pos = 0;
	}
}
