/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:24:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/07 17:20:46 by kbamping         ###   ########.fr       */
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

static int	ft_wait_child_pipe(int wait, char **cmds, int *curr, t_shell *s)
{
	pid_t	pid;
	int		status;
	int		flag;
	int		i;

	flag = EXIT_SUCCESS;
dprintf(2, "ft_wait_child_pipe( -- PARENT -- Start waiting --- pid = '%d' wait = '%d'\n", getpid(), wait); // debug
	wait = (wait == 0) ? WNOHANG : 0;
	if ((pid = waitpid(-1, &status, wait)) > 0)
	{
dprintf(2, "ft_wait_child_pipe() -- PARENT -- Finished waiting --- pid = '%d' caught child_pid '%d'\n", getpid(), pid); // debug

i = 0;
while (s->pipe.child_pid[i] != NULL)
{
	dprintf(2, "ft_wait_child_pipe() -- child_pid[%d] = '%s' -- pgid = '%d'\n", i, s->pipe.child_pid[i], getpgid(ft_atoi(s->pipe.child_pid[i])));
	++i;
}

		i = get_child_pid_index(pid, s);
		if (WIFEXITED(status) && (status = WEXITSTATUS(status) != EXIT_SUCCESS))
		{
dprintf(2, "ft_wait_child_pipe() -- '%d' NOT SUCCESSFUL -- status = '%d' status(+900) = '%d'\tpid = %d\n", i, status , status + 900, getpid()); // debug
//				flag = EXIT_FAILURE;
				err(((status == 1) ? 1 : status + 900), cmds[i]);	
		}
dprintf(2, "ft_wait_child_pipe() -- 2 -- status = '%d' status(+900) = '%d'\tpid = %d\n", status , status + 900, getpid()); // debug

		remove_child_pid(pid, s);
		if (i > *curr)
		{
			while (--i >= 0)
			{
dprintf(2, "ft_wait_child_pipe() -- killing previous child[%d]'%s'\n", i, s->pipe.child_pid[i]); // debug
				kill(ft_atoi(s->pipe.child_pid[i]), SIGKILL);
				remove_child_pid(ft_atoi(s->pipe.child_pid[i]), s);
		dprintf(2, "ft_wait_child_pipe() -- waiting for last child --  found '%d'\n", waitpid(-1, NULL, 0)); // debug
			}
			*curr = -1;
		}
		else
			--*curr;

	}
	else
dprintf(2, "ft_wait_child_pipe() -- PARENT -- NO CHILD finished yet --- pid = '%d' wait = '0'\n", pid); // debug

	return (flag);
}

static int	wait_for_children(char **cmds, t_shell *s)
{
	int		flag;
	int		c;


	c = 0;
	flag = EXIT_SUCCESS;
dprintf(2, "wait_for_children() -- START WAITING FOR ALL CHILD PIPES\n"); // debug
	while (s->pipe.child_pid && s->pipe.child_pid[c])
	{

		if (ft_wait_child_pipe(1, cmds, &c, s) != EXIT_SUCCESS)
			flag = EXIT_FAILURE;
		c++;
	}
dprintf(2, "wait_for_children() -- FINISHED WAITING FOR ALL CHILD PIPES\n"); // debug
	return (flag);
}

int			process_pipes(char *cmd, t_shell *s)
{
	pid_t			pid;
	int				n;
	int				status;
	char			**cmds;

	if ((status = init_pipes(cmd, &cmds, &n, s)) != EXIT_SUCCESS)
		return (status);
//	if ((defult_signal = signal(SIGCHLD, ft_sigchld_handler)) == SIG_IGN)
//		signal(SIGCHLD, SIG_IGN);
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
				err(status , cmds[s->pipe.pipe_i]);
			}
dprintf(2, "process_pipes() --- CHILD PROCESS returning, not exited --- ppid = %d\tpid = %d\n",
																				getppid(), getpid()); // debug
			free_t_shell(s);
dprintf(2, "process_pipes() -- 2 - child -- status = '%d'\tstatus(-900) = '%d'\tpid = %d\n", status, status-900, getpid()); // debug
			exit(status == 0 ? 0 : (status - 900));
		}
		// -----   Parent only   ------

// ADD CHILD PID TO ARRAY
		add_child_pid(pid, s);

dprintf(2, "process_pipes() -- PARENT  only area ------- ppid = %d\tpid = %d\n", getppid(), getpid()); // debug
		if (s->pipe.n_pipes)
		{
dprintf(2, "process_pipes() -- PARENT only area -- Do parent_pipe()  n_pipes = '%d' --- ppid = %d\tpid = %d\n",
													s->pipe.n_pipes, getppid(), getpid()); // debug
			parent_pipe(s);
		}

//dprintf(2, "process_pipes() -- PARENT --  nanosleep() -- START ------- pid = %d\n", getpid()); // debug
		ft_sleep(0, 500000);
//dprintf(2, "process_pipes() -- PARENT -- nanosleep() -- END ------- pid = %d\n", getpid()); // debug

		status = 0;
		ft_wait_child_pipe(0, cmds, &status, s);
		++s->pipe.pipe_i;
	}
	status = wait_for_children(cmds, s);
	reset_and_free_vars(&cmds, n, s);
	return ((status == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
