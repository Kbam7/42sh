/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 14:08:49 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 17:49:02 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_insert(t_shell *shell, char buff)
{
	int		i;
	char	*temp;

	temp = NULL;
	temp = (char *)malloc(sizeof(char) * (shell->str_len + 2));
	if (shell->new_line != NULL)
		temp = ft_strcpy(temp, shell->new_line);
	if (shell->curs_pos != shell->str_len)
	{
		i = shell->str_len;
		while (i >= shell->curs_pos)
		{
			temp[i + 1] = temp[i];
			i--;
		}
		temp[shell->curs_pos] = buff;
	}
	else if (buff)
		temp[shell->str_len] = buff;
	temp[shell->str_len + 1] = '\0';
	shell->new_line = ft_strdup(temp);
	free(temp);
}

void	ft_put_string(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->curs_col)
	{
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
		i++;
	}
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	tputs(tgetstr("cd", 0), 1, ft_putchar_re);
	write(1, "$> ", 2);
	ft_putstr(shell->new_line);
}

void	ft_put_curs(t_shell *shell)
{
	int		i;

	i = (shell->cols) - shell->curs_col;
	while (i-- > 0)
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	if ((shell->curs_pos + 3) % (shell->width) == 0)
	{
		tputs(tgetstr("do", 0), 1, ft_putchar_re);
		i = 0;
	}
	else if (shell->cols == 0)
		i = ft_curs_pos(shell) + 3;
	else
		i = ft_curs_pos(shell);
	while (i-- > 0)
		tputs(tgetstr("nd", 0), 1, ft_putchar_re);
}

void	ft_print_char(char *buff, t_shell *shell)
{
	if (buff[0] >= 32 && buff[0] <= 126 && buff[1] == 0 && buff[2] == 0)
	{
		ft_nbr_cols(shell);
		ft_curs_col(shell);
		ft_insert(shell, buff[0]);
		ft_put_string(shell);
		ft_put_curs(shell);
		shell->curs_pos++;
		shell->str_len++;
		shell->new_line[shell->str_len] = '\0';
	}
}

void	ft_enter(char *buff, t_shell *shell)
{
	if (buff[0] == 10 && buff[1] == 0 && buff[2] == 0)
	{
		ft_putchar('\n');
		shell->new_line[shell->str_len + 1] = '\0';
		ft_new_history(shell);
		shell->h_index++;
		shell->curs_pos = 0;
		shell->str_len = 0;
		shell->h_pos = 0;
		ft_execmd(shell);
		if (shell->new_line != NULL)
			free(shell->new_line);
		shell->new_line = NULL;
		write(1, "$> ", 2);
	}	
}
