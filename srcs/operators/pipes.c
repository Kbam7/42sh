/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:24:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/07 22:02:11 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	reset_and_free_vars(char ***cmds, size_t n_cmds, t_shell *s)
{
	s->pipe.n_pipes = 0;
	s->pipe.pipe_i = 0;
	free_tab((void ***)&s->pipe.pipes, n_cmds);
	free_tab((void ***)cmds, n_cmds);
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
	if ((s->pipe.pipes = (int **)malloc(sizeof(int *) * *n_cmds)) == NULL)
		return (err(ERR_MALLOC, "process_pipes() -- init_pipes()"));
	i = -1;
	while (++i < *n_cmds)
	{
		if ((s->pipe.pipes[i] = (int *)malloc(sizeof(int) * 2)) == NULL)
			return (err(ERR_MALLOC, "init_pipes()"));
		if (pipe(s->pipe.pipes[i]) == -1)
			return (err(ERR_CREATE_PIPE, "init_pipes()"));
	}
	return (EXIT_SUCCESS);
}

static void	process_pipes_two(char **cmds, pid_t pid, int *status, t_shell *s)
{
		add_child_pid(pid, s);
		if (s->pipe.n_pipes)
			parent_pipe(s);
		ft_sleep(0, 500000);
		*status = 0;
		ft_wait_child_pipe(0, cmds, status, s);
}

int			process_pipes(char *cmd, t_shell *s)
{
	pid_t			pid;
	int				n;
	int				status;
	char			**cmds;

	if ((status = init_pipes(cmd, &cmds, &n, s)) != EXIT_SUCCESS)
		return (status);
	while (cmds[s->pipe.pipe_i] && (s->pipe.n_pipes = n - s->pipe.pipe_i) > 0)
	{
		if ((pid = fork()) < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
		{
			if ((status = process_input(cmds[s->pipe.pipe_i], s)) != EXIT_SUCCESS)
				err(status , cmds[s->pipe.pipe_i]);
			free_t_shell(s);
			exit(status == 0 ? 0 : (status - 900));
		}
		process_pipes_two(cmds, pid, &status, s);
		++s->pipe.pipe_i;
	}
	status = wait_for_children(cmds, s);
	reset_and_free_vars(&cmds, n, s);
	return ((status == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
