/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:29:52 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 20:35:34 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		shell_loop(t_shell *s)
{
	int	ret;

	while (42)
	{
		set_prompt(s);
		ft_putstr(s->prompt);
		if ((ret = get_input(s) > 0))
		{
			ret = execute_cmd(s);
			free_tab(s->input, ft_tablen(s->input));
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
	{
		ft_putstr_fd("Error! fork failed\n", 2);
		return (status);
	}
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
