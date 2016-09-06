/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 13:05:23 by kgani             #+#    #+#             */
/*   Updated: 2016/09/06 09:54:04 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	ft_wait_str(int trigger, t_shell *s)
{
	int i;

	i = 0;
	while (s->new_line[i])
	{
		if (s->new_line[i] == trigger)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_wait_enter(char *buff, int trigger, t_shell *s, int *f_line)
{
	char *temp;

	if (buff[0] == 10 && buff[1] == 0 && buff[2] == 0)
	{
		ft_putchar('\n');
		s->curs_pos = 0;
		s->str_len = 0;
		if (s->new_line)
		{
			if (*f_line != 0)
				ft_echo_addstr(&s->wait_str, '\n');
			temp = ft_strdup(s->wait_str);
			ft_strdel(&s->wait_str);
			s->wait_str = ft_strjoin(temp, s->new_line);
			if (temp)
				ft_strdel(&temp);
		}
		if (s->new_line && ft_wait_str(trigger, s))
			return (1);
		ft_prompt_print(s);
		if (s->new_line)
			ft_strdel(&s->new_line);
		*f_line = 1;
	}
	return (0);
}

static int	ft_wait_edition(char *buff, int trigger, t_shell *s, int *f_line)
{
	ft_move_down(s, buff);
	ft_move_up(s, buff);
	ft_left_word(s, buff);
	ft_right_word(s, buff);
	ft_move_left(s, buff);
	ft_move_right(s, buff);
	ft_backspace(s, buff);
	ft_ctrl_l(buff, s);
	ft_history_up(s, buff);
	ft_history_down(s, buff);
	ft_end_right(s, buff);
	ft_end_left(s, buff);
	ft_autocomplete(s, buff);
	if (ft_wait_enter(buff, trigger, s, f_line))
		return (1);
	return (0);
}

static void	ft_wait_loop(t_shell *s, int trigger)
{
	int		f_line;
	char	*temp;

	f_line = 0;
	if ((temp = (char *)malloc(sizeof(char) * 6)) == NULL)
		return ;
	while (1)
	{
		ft_bzero(temp, 6);
		read(1, temp, 6);
		if (ft_wait_edition(temp, trigger, s, &f_line))
			break ;
		ft_print_char(temp, s);
	}
	if (s->wait_str)
	{
		s->new_line = ft_strdup(s->wait_str);
		free(s->wait_str);
		s->wait_strlen = 0;
	}
	free(temp);
}

void		ft_wait(int trigger, t_shell *s)
{
	char *tmp;

	if (s->new_line != NULL)
	{
		tmp = ft_strjoin(s->new_line, "\n");
		s->wait_str = ft_strdup(tmp);
		s->wait_strlen = ft_strlen(s->wait_str);
		free(tmp);
		tmp = NULL;
		free(s->new_line);
		s->new_line = NULL;
		s->curs_pos = 0;
		s->str_len = 0;
	}
	if (trigger == 34)
		ft_prompt_new("dquote> ", s);
	else if (trigger == 39)
		ft_prompt_new("quote> ", s);
	else if (trigger == 92)
		ft_prompt_new("bslash> ", s);
	ft_prompt_print(s);
	ft_wait_loop(s, trigger);
	ft_prompt_new("$> ", s);
}
