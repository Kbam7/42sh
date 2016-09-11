/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_suspend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 10:37:11 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 10:32:01 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_resume(int sig)
{
	(void)sig;
	puts("resuming terminal");
}

void	ft_signal_suspend(void)
{
	t_shell *s;

	s = ft_get_shell();
	if (s->fork_pid != 0)
	{
		signal(SIGTSTP, ft_resume);
	}
}
