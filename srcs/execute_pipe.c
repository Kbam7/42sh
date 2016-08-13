/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 01:56:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/13 01:57:07 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	child_pipe(t_shell *s)
{
	int	i;

	i = s->pipe.pipe_i;
	if (i == 0) // first cmd
	{
		dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
		close(s->pipe.pipes[i][0]);						// close STDOUT and write to pipe[i + 1]
		close(s->pipe.pipes[i][1]);						// close STDOUT and write to pipe[i + 1]
	}
	else if (s->pipe.n_pipes == 1) // last pipe
	{
		dup2(s->pipe.pipes[i][0], STDIN_FILENO); // read from current pipe
		close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
		close(s->pipe.pipes[i][1]);	// close last write-end, STDOUT used
	}
	else
	{
		close(s->pipe.pipes[i][1]);	// close this pipe, writing to next pipe
		dup2(s->pipe.pipes[i][0], STDIN_FILENO); // read from current pipe
		close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
		dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
	}
}

void	parent_pipe(t_shell *s)
{
	int	i;

	i = s->pipe.pipe_i;
	if (i == 0) // first cmd
	{
			close(s->pipe.pipes[i][0]);		// close pipe[0], not reading from first pipe
			close(s->pipe.pipes[i][1]);		// close pipe[1], not writing to first pipe
	}
	else if (s->pipe.n_pipes == 1) // last pipe
	{
			close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
			close(s->pipe.pipes[i][1]);	// close last write-end, STDOUT used
	}
	else
	{
			close(s->pipe.pipes[i][0]);	// STDIN reading from pipe[i][0]
			close(s->pipe.pipes[i][1]);	// STDOUT writing to pipe[i +1][1]
	}
}
