/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 01:56:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/20 13:19:33 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	child_pipe(t_shell *s)
{
	int	i;

	i = s->pipe.pipe_i;
	if (i == 0) // first cmd
	{
dprintf(2, "child_pipe() -- first_pipe -- n_pipes == '%d'\n", s->pipe.n_pipes); // debug
		dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
		close(s->pipe.pipes[i][0]);						// close STDOUT and write to pipe[i + 1]
		close(s->pipe.pipes[i][1]);						// close STDOUT and write to pipe[i + 1]
	}
	else 
	{
		if (s->pipe.n_pipes == 1) /*last pipe*/ dprintf(2, "child_pipe() -- last_pipe -- n_pipes == '%d'\n", s->pipe.n_pipes); // debug

		close(s->pipe.pipes[i][1]);	// close last write-end, STDOUT used
		dup2(s->pipe.pipes[i][0], STDIN_FILENO); // read from current pipe
		close(s->pipe.pipes[i][0]);	// STDIN reading from pipe
		if (s->pipe.n_pipes > 1) // NOT last pipe, write to next pipe
			dup2(s->pipe.pipes[i + 1][1], STDOUT_FILENO);
	}
dprintf(2, "child_pipe() -- END\n"); // debug
}

void	parent_pipe(t_shell *s)
{
dprintf(2, "parent_pipe() -- START\n"); // debug
	int	i;

	i = s->pipe.pipe_i;
//	if (s->redir.n_rdr == 1)
//		dup2(s->pipe.pipes[i][0], STDIN_FILENO);
	close(s->pipe.pipes[i][0]);
	close(s->pipe.pipes[i][1]);
dprintf(2, "parent_pipe() -- END\n"); // debug
}
