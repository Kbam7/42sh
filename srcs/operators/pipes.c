/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:24:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/06 20:54:00 by kbamping         ###   ########.fr       */
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
			return (err(ERR_MALLOC, "init_pipes()"));
		if (pipe(s->pipe.pipes[i]) == -1)
			return (err(ERR_CREATE_PIPE, "init_pipes()"));
	}
	return (EXIT_SUCCESS);
}

static int	wait_for_children(int n_cmds, t_shell *s)
{
	int				status;
	int				flag;

	s->pipe.pipe_i = 0;
	flag = EXIT_SUCCESS;
	while ((s->pipe.n_pipes = n_cmds - s->pipe.pipe_i) > 0)
	{
dprintf(2, "wait_for_children() -- PARENT -- Waiting for child ------- pid = %d\n", getpid()); // debug
		wait(&status);
dprintf(2, "wait_for_children() -- PARENT -- Finished waiting ------- pid = %d\n", getpid()); // debug

		if (WIFEXITED(status) && (status = WEXITSTATUS(status)) != EXIT_SUCCESS)
		{
dprintf(2, "wait_for_children() -- 1 -- status = '%d' status(+900) = '%d'\tpid = %d\n", status , status + 900, getpid()); // debug
			++flag;
			err(((status == 1) ? 1 : status + 900), ""/*s->input[0]*/);	
		}

		
dprintf(2, "wait_for_children() -- 2 -- status = '%d' status(+900) = '%d'\tpid = %d\n", status , status + 900, getpid()); // debug
		++s->pipe.pipe_i;
	}
	return (flag);
}

int			process_pipes(char *cmd, t_shell *s)
{
	struct timespec	time;
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

dprintf(2, "process_pipes() --- START -- CHILD PROCESS --- ppid = %d\tpid = %d\n"
						"process_pipes() - child -- Calling process_input() with '%s' ...\n\n",
						getppid(), getpid(), cmds[s->pipe.pipe_i]); // debug


			if ((status = process_input(cmds[s->pipe.pipe_i], s)) != EXIT_SUCCESS)
			{
dprintf(2, "process_pipes() -- process_input() NOT SUCCESSFULL!\tstatus = %d\tpid = %d\n", status, getpid()); // debug
			}
dprintf(2, "process_pipes() --- CHILD PROCESS returning, not exited --- ppid = %d\tpid = %d\n",
																				getppid(), getpid()); // debug
			free_t_shell(s);
dprintf(2, "process_pipes() -- 2 - child -- status = '%d'\tstatus(-900) = '%d'\tpid = %d\n", status, status-900, getpid()); // debug
			exit(status == 0 ? 0 : (status - 900));
		}
		// -----   Parent only   ------

// ADD CHILD PID TO ARRAY

dprintf(2, "process_pipes() -- PARENT  only area ------- ppid = %d\tpid = %d\n", getppid(), getpid()); // debug
		if (s->pipe.n_pipes)
		{
dprintf(2, "process_pipes() -- PARENT only area -- Do parent_pipe()  n_pipes = '%d' --- ppid = %d\tpid = %d\n",
													s->pipe.n_pipes, getppid(), getpid()); // debug
			parent_pipe(s);
		}
		time.tv_sec = 0;
		time.tv_nsec = 10000000/*000000*/;
dprintf(2, "process_pipes() -- PARENT --  nanosleep() -- START ------- pid = %d\n", getpid()); // debug
		nanosleep(&time, NULL);
dprintf(2, "process_pipes() -- PARENT -- nanosleep() -- END ------- pid = %d\n", getpid()); // debug
		++s->pipe.pipe_i;
	}

	status = wait_for_children(n, s);

	reset_and_free_vars(cmds, n, s);
	return ((status == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
