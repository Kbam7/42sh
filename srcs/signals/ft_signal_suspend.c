/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_suspend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 10:37:11 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 06:45:48 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void ft_signal_suspend(void)
{
	t_shell *s;

	s = ft_get_shell();
	if (s->fork_pid != 0)
	{
		kill(s->fork_pid, SIGTSTP);
		kill(getppid(), SIGCONT);
		pause();
	}

}
