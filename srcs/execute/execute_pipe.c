/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 01:56:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 13:12:08 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	child_pipe(t_shell *s)
{
	int	i;

	i = s->pipe.pipe_i;
	if (i == 0)
	{
		dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
		close(s->pipe.pipes[i][0]);
		close(s->pipe.pipes[i][1]);
	}
	else
	{
		close(s->pipe.pipes[i][1]);
		dup2(s->pipe.pipes[i][0], STDIN_FILENO);
		close(s->pipe.pipes[i][0]);
		if (s->pipe.n_pipes > 1)
			dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
	}
}

void	parent_pipe(t_shell *s)
{
	int	i;

	i = s->pipe.pipe_i;
	close(s->pipe.pipes[i][0]);
	close(s->pipe.pipes[i][1]);
}
