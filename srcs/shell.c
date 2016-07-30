/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:29:52 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 02:01:56 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		shell_loop(t_shell *s)
{
	int			ret;
	t_cmd_list	*command;

	while (42)
	{
		set_prompt(s);
		ft_putstr(s->prompt);
		if ((ret = get_commands(s) > 0))
		{
			command = s->command;
			while (command != NULL) // ! end of cmd_list
			{
				get_input(command);
				ret = execute_cmd(s);
				command = command->next;
			}
//			free_tab(s->input, ft_tablen(s->input));
			free_cmd_list(s->commands);
			if (ret == EXIT_SH)
				break ;
		}
	}
}

static int	launch_shell(t_shell *s)
{
	if (execve(ft_getenv("21SH_PATH", s), s->argv, s->env_var) != -1)
		exit(EXIT_SUCCESS);
	err(ERR_EXEC_SHELL, ft_getenv("21SH_PATH", s));
	free_tab(s->input, ft_tablen(s->input));
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

void	free_t_shell(t_shell *s)
{
	free_tab(s->env_var, ft_tablen(s->env_var));
	free_tab(s->shell_var, ft_tablen(s->shell_var));
	free_tab(s->paths, ft_tablen(s->paths));
	free_tab(s->argv, ft_tablen(s->argv));
	ft_strdel(&s->prompt);
}
