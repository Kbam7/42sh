/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:24:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/05 14:33:10 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		process_pipes(char *cmd, t_shell *s)
{
	t_split_string	sub_cmd;
	char			**tmp;
	size_t				i;

	sub_cmd = ft_nstrsplit(cmd, '|');
	tmp = tab_trim(sub_cmd.strings, (int)sub_cmd.words);
	free_tab((void **)sub_cmd.strings, sub_cmd.words);
	sub_cmd.strings = ft_tabdup(tmp, sub_cmd.words);
	free_tab((void **)tmp, sub_cmd.words);

//dprintf(2, "process_pipe() ---- Here - 1\n"); // debug

	// Create int **array for pipes
	s->pipe.pipes = (int **)malloc(sizeof(int *) * sub_cmd.words);
	i = 0;
	while (i < sub_cmd.words)
	{
		s->pipe.pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(s->pipe.pipes[i]) == -1)
			return (err(ERR_CREATE_PIPE, "execute_cmd()"));
		++i;
	}

//dprintf(2, "process_pipe() ---- Here - 2\n"); // debug

	// loop through sub_cmd.strings[] and execute
	while (sub_cmd.strings[s->pipe.pipe_i] && (s->pipe.n_pipes = sub_cmd.words - s->pipe.pipe_i) > 0)
	{
		i = s->pipe.pipe_i;
		if (s->pipe.n_pipes == 1 && sub_cmd.strings[i] == NULL)
		{

//dprintf(2, "process_pipe() ---- Here  - 2.1 -- s->n->pipe.pipes = %d\tsub_cmd.strings[i] = >%s< -- NULL\n",
//																		s->pipe.n_pipes, sub_cmd.strings[i]); // debug

		// user has input "cat author |", there is no command after the pipe so
		//	read one line(ft_gnl), and use that line as a command. This command may be
		//	multiple commands piped together, so running the input through from
		//	the top of the program would be a good idea.
		//	basically, fork, and run shell_loop() again. Make sure to pipe the STDOUT
		//	into the write-end of the pipe (s->pipe_fd[1]). Then this parent which
		//	is the parent of shell_loop, waits for the child and then uses the pipe
		}
		else
		{

//dprintf(2, "process_pipe() ---- Here  - 2.2 -- s->n->pipe.pipes = %d\tsub_cmd.strings[i] = >%s<\n", s->pipe.n_pipes, sub_cmd.strings[i]); // debug

			process_input(sub_cmd.strings[i], s);
		}
// At this point, the output has been read into the pipe or to the screen if its the last command.
		++s->pipe.pipe_i;
	}

//dprintf(2, "process_pipe() ---- Here - 3 -- s->pipe.n_pipes = %d\n", s->pipe.n_pipes); // debug

	s->pipe.n_pipes = 0;
	s->pipe.pipe_i = 0;
	free_tab((void **)s->pipe.pipes, s->pipe.pipe_i);
	free_tab((void **)sub_cmd.strings, ft_tablen(sub_cmd.strings));
	return (EXIT_SUCCESS);
}
