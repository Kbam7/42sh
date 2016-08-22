/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_back_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 12:31:10 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 15:46:20 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_line_back_space(t_shell *shell)
{
    int     i;
    int		j;

    if (shell->curs_pos != shell->str_len)
    {
        i = shell->curs_pos;
        j = i;
        while (i <= shell->str_len - 1)
        {
            if (shell->new_line[j - 1] == '\n')
                j++;
            shell->new_line[j - 1] = shell->new_line[i];
            i++;
            j++;
        }
        shell->new_line[shell->str_len] = '\0';
    }
    else
        shell->new_line[shell->curs_pos] = '\0';
    shell->new_line[shell->str_len - 1] = '\0';
}

void    ft_put_curs_back(t_shell *shell)
{
    int     i;
    int     j;

    j = shell->str_len + 2;
    while (j - shell->width > 0)
        j = j - shell->width;
    if (j != shell->width || shell->curs_pos != shell->str_len)
    tputs(tgetstr("cr", 0), 1, ft_putchar_re);
    if (shell->cols == 0)
        i = ft_curs_pos(shell) + 1;
    else
        i = ft_curs_pos(shell) - 2;
    while (i-- > 0)
        tputs(tgetstr("nd", 0), 1, ft_putchar_re);
    i = shell->cols - shell->curs_col;
     while (i-- > 0 && shell->str_len + 2 -
			 (shell->width * (shell->cols - 1)) != shell->width)
        tputs(tgetstr("up", 0), 1, ft_putchar_re);
    if ((shell->str_len + 1) == shell->width )
         tputs(tgetstr("do", 0), 1, ft_putchar_re);
     i = ft_curs_pos(shell) - 2;
    if (shell->curs_pos != shell->str_len && (shell->str_len + 1) -
			(shell->width * (shell->cols - 1)) == shell->width)
        while (i-- > 0)
            tputs(tgetstr("nd", 0), 1, ft_putchar_re);
    i = 0;
    if (shell->curs_pos != shell->str_len &&
			(ft_curs_pos(shell) == 1) && shell->curs_pos != 1)
    {
        tputs(tgetstr("up", 0), 1, ft_putchar_re);
        while (i++ < shell->width)
            tputs(tgetstr("nd", 0), 1, ft_putchar_re);
                
    }
    if (shell->curs_pos != shell->str_len &&
			((shell->str_len + 1) - (shell->width * (shell->cols - 1)) ==
			 shell->width) && shell->cols != 1)
        tputs(tgetstr("up", 0), 1, ft_putchar_re);
}

void	ft_back_clear(t_shell *shell)
{
    ft_put_string(shell);
    ft_put_curs_back(shell);
}

void    ft_backspace(t_shell *shell, char *buff)
{
    if (buff[0] == 127 && shell->curs_pos > 0)
    {
        ft_line_back_space(shell);
        ft_nbr_cols(shell);
        ft_curs_col(shell);
        ft_back_clear(shell);
        shell->curs_pos--;
        shell->str_len--;
    }
}
