/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:24:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/14 18:48:01 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	reset_and_free_vars(char **cmds, size_t n_cmds, t_shell *s)
{
dprintf(2, "process_pipes() -- START reset_and_free_vars()\tpid = %d\n", getpid()); // debug
	s->pipe.n_pipes = 0;
	s->pipe.pipe_i = 0;
	free_tab((void ***)&s->pipe.pipes, n_cmds);
	free_tab((void ***)&cmds, n_cmds);
dprintf(2, "process_pipes() -- END reset_and_free_vars()\tpid = %d\n", getpid()); // debug
}

static int	init_pipes(char *cmd, char ***cmds,  t_shell *s)
{
	t_split_string	split;
	char			**tmp;

	split = ft_nstrsplit(cmd, '|');
	tmp = tab_trim(split.strings, (int)split.words);
	free_tab((void ***)&split.strings, split.words);
	*cmds = ft_tabdup(tmp, split.words);
	free_tab((void ***)&tmp, split.words);
	// Create int **array for pipes
	if ((s->pipe.pipes = (int **)malloc(sizeof(int *) * split.words)) == NULL)
		return (err(ERR_MALLOC, "process_pipes() -- init_pipes()"));
	return (split.words);
}

int			process_pipes(char *cmd, t_shell *s)
{
	int		i;
	int		n_cmds;
	char	**cmds;

	if ((n_cmds = init_pipes(cmd, &cmds, s)) == ERR_MALLOC)
		return (n_cmds);
	i = -1;
	while (++i < n_cmds)
	{
		if ((s->pipe.pipes[i] = (int *)malloc(sizeof(int) * 2)) == NULL)
			return (err(ERR_MALLOC, "process_pipes()"));
		if (pipe(s->pipe.pipes[i]) == -1)
			return (err(ERR_CREATE_PIPE, "execute_cmd()"));
	}
	// loop through cmds[] and execute
	while (cmds[s->pipe.pipe_i] && (s->pipe.n_pipes = n_cmds - s->pipe.pipe_i) > 0)
	{
		if (s->pipe.n_pipes == 1 && cmds[s->pipe.pipe_i] == NULL)
		{
		// user has input "cat author |", there is no command after the pipe so
		//	read one line(ft_gnl), and use that line as a command. This command may be
		//	multiple commands piped together, so running the input through from
		//	the top of the program would be a good idea.
		//	basically, fork, and run shell_loop() again. Make sure to pipe the STDOUT
		//	into the write-end of the pipe (s->pipe_fd[1]). Then this parent which
		//	is the parent of shell_loop, waits for the child and then uses the pipe
		}
		else
			if ((i = process_input(cmds[s->pipe.pipe_i], s)) != EXIT_SUCCESS)
			{
dprintf(2, "process_pipes() -- process_input() NOT SUCCESSFULL!\ti = %d\tpid = %d\n", i, getpid()); // debug
				break ;
			}
// At this point, the output has been read into the pipe or to the screen if its the last command.
		++s->pipe.pipe_i;
	}
	reset_and_free_vars(cmds, n_cmds, s);
	return ((i == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
