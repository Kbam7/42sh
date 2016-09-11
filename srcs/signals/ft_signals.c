/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 10:48:11 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 10:32:22 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
		ft_signal_int();
	if (signal == SIGQUIT)
		ft_signal_quit();
	if (signal == SIGTSTP)
		ft_signal_suspend();
	if (signal == SIGSEGV)
		ft_signal_segv();
}

void		ft_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	signal(SIGTSTP, ft_signal_handler);
	signal(SIGSEGV, ft_signal_handler);
}
