/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 21:55:31 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 18:20:34 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_remove_previous_pid(int i, int *curr, t_shell *s)
{
	while (--i >= 0)
	{
		kill(ft_atoi(s->pipe.child_pid[i]), SIGKILL);
		remove_child_pid(ft_atoi(s->pipe.child_pid[i]), s);
		waitpid(-1, NULL, 0);
	}
	*curr = -1;
}

int			ft_wait_child_pipe(int wait, char **cmds, int *curr, t_shell *s)
{
	pid_t	pid;
	int		status;
	int		flag;
	int		i;

	flag = EXIT_SUCCESS;
	wait = (wait == 0) ? WNOHANG : 0;
	if ((pid = waitpid(-1, &status, wait)) > 0)
	{
		i = get_child_pid_index(pid, s);
		if (WIFEXITED(status) && (status = WEXITSTATUS(status) != EXIT_SUCCESS))
			err(((status == 1) ? 1 : status + 900), cmds[i]);
		remove_child_pid(pid, s);
		if (i > *curr)
			ft_remove_previous_pid(i, curr, s);
		else
			--*curr;
	}
	return (flag);
}

int			wait_for_children(char **cmds, t_shell *s)
{
	int		flag;
	int		c;

	c = 0;
	flag = EXIT_SUCCESS;
	while (s->pipe.child_pid && s->pipe.child_pid[c])
	{
		if (ft_wait_child_pipe(1, cmds, &c, s) != EXIT_SUCCESS)
			flag = EXIT_FAILURE;
		c++;
	}
	return (flag);
}
