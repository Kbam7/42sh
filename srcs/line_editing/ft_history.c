/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 09:33:16 by tmack             #+#    #+#             */
/*   Updated: 2016/09/09 11:56:51 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_new_history(t_shell *s)
{
	if (s->new_line)
	{
		s->history[s->h_index] = ft_strdup(s->new_line);
		s->h_index++;
	}
}

void	ft_history_up(t_shell *s, char *buff)
{
	int		i;

	i = 0;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 65 && buff[3] == 0 &&
			s->h_pos < s->h_index)
	{
		while (i < s->curs_col)
		{
			tputs(tgetstr("up", 0), 1, ft_putchar_re);
			i++;
		}
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
		tputs(tgetstr("cd", 0), 1, ft_putchar_re);
		ft_prompt_print(s);
		s->h_pos++;
		i = s->h_index - s->h_pos;
		if (s->new_line != NULL)
			free(s->new_line);
		s->new_line = ft_strdup(s->history[i]);
		ft_putstr(s->new_line);
		s->curs_pos = ft_strlen(s->new_line);
		s->str_len = ft_strlen(s->new_line);
	}
}

void	ft_history_down(t_shell *s, char *buff)
{
	int		i;

	i = 0;
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 66 &&
			buff[3] == 0 && s->h_pos > 1)
	{
		while (i < s->curs_col)
		{
			tputs(tgetstr("up", 0), 1, ft_putchar_re);
			i++;
		}
		tputs(tgetstr("cr", 0), 1, ft_putchar_re);
		tputs(tgetstr("cd", 0), 1, ft_putchar_re);
		ft_prompt_print(s);
		s->h_pos--;
		i = s->h_index - s->h_pos;
		if (s->new_line != NULL)
			free(s->new_line);
		s->new_line = ft_strdup(s->history[i]);
		ft_putstr(s->new_line);
		s->curs_pos = ft_strlen(s->new_line);
		s->str_len = ft_strlen(s->new_line);
	}
}
