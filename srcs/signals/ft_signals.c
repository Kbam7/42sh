/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 10:48:11 by kgani             #+#    #+#             */
/*   Updated: 2016/09/06 16:58:41 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void ft_signal_int()
{
	t_shell	*s;

	s = ft_get_shell();
	if (s->fork_pid == 0)
	{
		ft_putchar('\n');
		ft_prompt_print(s);
	}
	else
		kill(s->fork_pid, SIGKILL);

}

static void ft_signal_handler(int signal)
{
	if (signal == SIGINT)
		ft_signal_int();
}

void ft_signals(void)
{
	signal(SIGINT, ft_signal_handler);
}
