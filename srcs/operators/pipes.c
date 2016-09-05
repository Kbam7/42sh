/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:24:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/05 18:57:26 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	reset_and_free_vars(char **cmds, size_t n_cmds, t_shell *s)
{
	s->pipe.n_pipes = 0;
	s->pipe.pipe_i = 0;
	free_tab((void ***)&s->pipe.pipes, n_cmds);
	free_tab((void ***)&cmds, n_cmds);
}

static int	init_pipes(char *cmd, char ***cmds, int *n_cmds, t_shell *s)
{
	t_split_string	split;
	char			**tmp;
	int				i;

	split = ft_nstrsplit(cmd, '|');
	*n_cmds = (int)split.words;
	tmp = tab_trim(split.strings, *n_cmds);
	free_tab((void ***)&split.strings, *n_cmds);
	*cmds = ft_tabdup(tmp, *n_cmds);
	free_tab((void ***)&tmp, *n_cmds);
	// Create int **array for pipes
	if ((s->pipe.pipes = (int **)malloc(sizeof(int *) * *n_cmds)) == NULL)
		return (err(ERR_MALLOC, "process_pipes() -- init_pipes()"));
	i = -1;
	while (++i < *n_cmds)
	{
		if ((s->pipe.pipes[i] = (int *)malloc(sizeof(int) * 2)) == NULL)
			return (err(ERR_MALLOC, "process_pipes()"));
		if (pipe(s->pipe.pipes[i]) == -1)
			return (err(ERR_CREATE_PIPE, "execute_cmd()"));
	}
	return (EXIT_SUCCESS);
}

int			process_pipes(char *cmd, t_shell *s)
{
	int		i;
	int		n;
	char	**cmds;

	if ((i = init_pipes(cmd, &cmds, &n, s)) != EXIT_SUCCESS)
		return (i);
	while (cmds[s->pipe.pipe_i] && (s->pipe.n_pipes = n - s->pipe.pipe_i) > 0)
	{
		if (s->pipe.n_pipes == 1 && cmds[s->pipe.pipe_i] == NULL)
		{
		// user has input "cat author |", there is no command after the pipe so
		//	read one line(ft_gnl), and use that line as a command. This command may be
		//	multiple commands piped together. i.e. a string of cmds
		}
		else
			if ((i = process_input(cmds[s->pipe.pipe_i], s)) != EXIT_SUCCESS)
			{
dprintf(2, "process_pipes() -- process_input() NOT SUCCESSFULL!\treturn = %d\tpid = %d\n", i, getpid()); // debug
		//		break ;
			}
// At this point, the output has been read into the pipe or to the screen if its the last command.
		++s->pipe.pipe_i;
	}
	reset_and_free_vars(cmds, n, s);
	return ((i == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}

/*

*/
