/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 16:48:49 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 17:40:41 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_clear_screen(void)
{
	char	buf[2048];
	char	*str;

	tgetent(buf, getenv("TERM"));
	str = tgetstr("cl", NULL);
	ft_putendl(str);
}

int		ft_putchar_re(int c)
{
	return (write(0, &c, 1));
}

int		init_terminal_data(t_shell *shell, char **env)
{
	shell->env = NULL;
	shell->env = ft_strdup_2(env);
    shell->pwd = NULL;
    shell->oldpwd = NULL;
	shell->curs_pos = 0;
	shell->str_len = 0;
	shell->cols = 0;
	shell->curs_col = 0;
	shell->on = 0;
    shell->nbr_space = 0;
	shell->h_index = 0;
	shell->h_pos = 0;
	shell->nbr_semi = 0;
	if (tgetent(0, getenv("TERM")) < 1)
		return (-1);
    shell->hight = tgetnum("li");
    shell->width = tgetnum("co");
    ft_path(shell);
    ft_home_path(shell);
    ft_user(shell);
	shell->new_line = NULL;
	shell->history = (char **)malloc(sizeof(char *) * 1024);
	tcgetattr(0, &shell->new_term);
	shell->new_term.c_lflag &= ~(ICANON | ECHO);
	shell->new_term.c_cc[VMIN] = 1;
	shell->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &shell->new_term);
	tputs(tgetstr("ti", 0), 1, ft_putchar_re);
	return (1);
}
