/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 16:48:49 by tmack             #+#    #+#             */
/*   Updated: 2016/08/26 11:14:57 by tmack            ###   ########.fr       */
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

int		init_terminal_data(t_shell *s, char **env)
{
	char	*term;
	int		ret;

	s->env = NULL;
	s->env = ft_strdup_2(env);
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
/////////[ START ]///////////
	term = ttyname(0);
	s->term_fd = open(term, O_RDWR | O_NONBLOCK);
//	free(term);
	if (!(term = ft_getenv("TERM")))
		err(/*ERR_NO_TERMTYPE*/0, "");
	if ((ret = tgetent(NULL, term)) < 1)
	{
		if (ret == 0)
			err(/*ERR_NO_ENTRY*/0, term);
		else
			err(/*ERR_NODB*/0, "");
	}
/////////[ END ]///////////
    s->hight = tgetnum("li");
    s->width = tgetnum("co");
    s->home_path = ft_getenv("HOME", s);
    s->user = ft_getenv("USER", s);
	s->history = NULL;
	s->new_line = NULL;
	s->new_line = (char *)malloc(sizeof(char) + 2);
	ft_bzero(s->new_line, 2);
	s->history = (char **)malloc(sizeof(char *) * 1024);
/////////[ START ]///////////
	if ((tcgetattr(STDIN_FILENO, &s->default_term)) < 0)
		err(/*ERR_CANT_RETRIEVE_TERM_ATTR*/0, term);
	s->new_term = s->default_term;
	s->new_term.c_lflag |= ISIG;
	s->new_term.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE);
	s->new_term.c_cc[VMIN] = 1;
	s->new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s->new_term);
	tputs(tgetstr("ti", NULL), 1, ft_putchar_re);
//	tputs(tgetstr("vi", NULL), 1, ft_putchar_re);
/////////[ END ]///////////
	return (1);
}
/*
int		init_terminal_data(t_shell *s, char **env)
{
	s->env = NULL;
	s->env = ft_strdup_2(env);
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
//	s->nbr_semi = 0;
	if (tgetent(0, getenv("TERM")) < 1)
		return (-1);
    s->hight = tgetnum("li");
    s->width = tgetnum("co");
//    ft_path(s);
    s->home_path = ft_getenv("HOME", s);
    s->user = ft_getenv("USER", s);
	s->history = NULL;
	s->new_line = NULL;
	s->new_line = (char *)malloc(sizeof(char) + 2);
	ft_bzero(s->new_line, 2);
	s->history = (char **)malloc(sizeof(char *) * 1024);
	tcgetattr(0, &s->new_term);
	s->new_term.c_lflag &= ~(ICANON | ECHO);
	s->new_term.c_cc[VMIN] = 1;
	s->new_term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &s->new_term);
	tputs(tgetstr("ti", 0), 1, ft_putchar_re);
	return (1);
}
*/
