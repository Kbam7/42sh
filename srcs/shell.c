/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:29:52 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/14 19:21:52 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		shell_loop(t_shell *s)
{
	int			ret;
	t_cmd_list	*cmd_list;

	ret = 0;
	while (ret != EXIT_SH)
	{
//dprintf(2, "shell_loop() -- START -- \tpid = %d\n", getpid()); // debug
		set_prompt(s);
		ft_putstr(s->prompt);
//dprintf(2, "shell_loop() -- printed prompt -- \tpid = %d\n", getpid()); // debug
		if ((ret = get_commands(s) > 0))
		{
			cmd_list = s->commands;
			while (cmd_list != NULL)
			{
				ret = process_input(cmd_list->cmd, s);
//dprintf(2, "shell_loop() -- ret = %d\tpid = %d\n", ret, getpid()); // debug
				if (ret == EXIT_SH || ret == EXIT_FAILURE)
					break ;
				cmd_list = cmd_list->next;
			}
//dprintf(2, "shell_loop() -- break cmd loop, freeing cmds\tpid = %d\n", getpid()); // debug
			free_cmd_list(&s->commands);
		}
	}
//dprintf(2, "shell_loop() -- Ending --\tppid = %d\tpid = %d\n", getppid(), getpid()); // debug
}

static int	launch_shell(t_shell *s)
{
	if (execve(ft_getenv("21SH_PATH", s), s->argv, s->env_var) != -1)
		exit(EXIT_SUCCESS);
	err(ERR_EXEC_SHELL, ft_getenv("21SH_PATH", s));
	free_tab((void ***)&s->input, ft_tablen(s->input));
	free_t_shell(s);
	exit(EXIT_FAILURE);
}

int			run_shell(t_shell *s)
{
	pid_t	pid;
	int		status;

	status = EXIT_FAILURE;
	pid = fork();
	if (pid < 0)
		return (err(ERR_FORK_FAILED, ""));
	if (pid == 0)
		launch_shell(s);
	wait(&status);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int			free_t_shell(t_shell *s)
{
	if (s->commands != NULL)
		free_cmd_list(&s->commands);
	if (s->input != NULL)
		free_tab((void ***)&s->input, ft_tablen(s->input));
	if (s->redir.rdr != NULL)
		free_tab((void ***)&s->redir.rdr, ft_tablen(s->redir.rdr));
	if (s->redir.cmd != NULL)
		free_tab((void ***)&s->redir.cmd, ft_tablen(s->redir.cmd));
	if (s->redir.pipe != NULL)
		free_pipes(&s->redir.pipe, ft_pipelen(s->redir.pipe));

	free_tab((void ***)&s->env_var, ft_tablen(s->env_var));
	free_tab((void ***)&s->shell_var, ft_tablen(s->shell_var));
	free_tab((void ***)&s->paths, ft_tablen(s->paths));
	free_tab((void ***)&s->argv, ft_tablen(s->argv));
	ft_strdel(&s->prompt);
	return (EXIT_SUCCESS);
}
