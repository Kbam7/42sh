/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 16:48:49 by tmack             #+#    #+#             */
/*   Updated: 2016/09/04 09:45:01 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_clear_screen(void)
{
	char	buf[2048];
	char	*str;

	tgetent(buf, getenv("TERM"));
	str = tgetstr("cl", NULL);
	ft_putstr(str);
}

int		ft_putchar_re(int c)
{
	return (write(0, &c, 1));
}

static void	init_terminal_vars(t_shell *s)
{
    s->pwd = NULL;
    s->oldpwd = NULL;
	s->curs_pos = 0;
	s->str_len = 0;
	s->cols = 0;
	s->curs_col = 0;
	s->on = 0;
    s->nbr_space = 0;
	s->h_index = 0;
	s->h_pos = 0;
	s->new_line = NULL;
	s->history = NULL;
	s->prompt = ft_strdup("moo$> ");
	s->prompt_len = 6;

}

int		init_terminal_data(t_shell *s, char **env)
{
	char	*buf;
	char	*term;
	int		ret;
    char *os = ft_strdup(env[0]);

    free(os);
	buf = ft_strnew(2048);
	init_terminal_vars(s);
	s->env = NULL;
	s->env = ft_strdup_2(env);
	term = ft_getenv("TERM", s);
	if ((ret = tgetent(buf, term)) < 1)
			err(/*(ret == 0) ? ERR_NO_ENTRY : ERR_NODB */0, term);
	ft_strdel(&buf);
    s->hight = tgetnum("li");
    s->width = tgetnum("co");
    s->home_path = ft_getenv("HOME", s);
    s->user = ft_getenv("USER", s);
	s->new_line = (char *)malloc(sizeof(char) + 2);
	ft_bzero(s->new_line, 2);
	s->history = (char **)malloc(sizeof(char *) * 1024);
	if ((tcgetattr(STDIN_FILENO, &s->default_term)) < 0)
		err(/*ERR_NO_TERM_ATTR*/0, term);
	s->new_term = s->default_term;
	s->new_term.c_lflag |= ISIG;
	s->new_term.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE);
	s->new_term.c_cc[VMIN] = 1;
	s->new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s->new_term);
	tputs(tgetstr("ti", NULL), 1, ft_putchar_re);
	return (1);
}
