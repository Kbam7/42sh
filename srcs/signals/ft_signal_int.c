/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 11:02:18 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 06:30:05 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void ft_signal_int()
{
	t_shell *s;

	s = ft_get_shell();
	if (s->fork_pid == 0)
	{
		ft_putchar('\n');
		s->curs_pos = 0;
		s->str_len = 0;
		s->h_pos = 0;
		ft_strdel(&s->new_line);
		s->new_line = (char *)malloc(sizeof(char) + 1);
		s->new_line[0] = '\0';
		ft_prompt_print(s);
	}
	else
	{
		free_t_shell(s);
		kill(s->fork_pid, SIGKILL);
	}

}
