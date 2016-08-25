/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:29:52 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/25 14:55:30 by kbamping         ###   ########.fr       */
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
//		set_prompt(s);
	//	ft_printf("%s%s%s%s", C_BOLD, C_BROWN, s->prompt, C_NONE);
		write(1, "$> ", 2);
		while (s->commands == NULL)
			buffer(s);

dprintf(2, "shell_loop() -- HERE\n"); // debug
	
		cmd_list = s->commands;
		while (cmd_list != NULL)
		{
			ret = process_input(cmd_list->cmd, s);
			if (ret == EXIT_SH || ret == EXIT_FAILURE)
				break ;
			cmd_list = cmd_list->next;
		}
		free_cmd_list(&s->commands);
	}
}
/*
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
*/
static void	ft_exit(void)
{
    tputs(tgetstr("ve", 0), 1, ft_putchar_re);
    tputs(tgetstr("te", 0), 1, ft_putchar_re);
//    tputs(tgetstr("rs", 0), 1, ft_putchar_re);
	exit(1);
}

int			free_t_shell(t_shell *s)
{
	if (s->commands != NULL)
		free_cmd_list(&s->commands);
	if (s->input != NULL)
		free_tab((void ***)&s->input, ft_tablen(s->input));
	if (s->pipe.pipes != NULL)
		free_tab((void ***)&s->pipe.pipes, (s->pipe.n_pipes + s->pipe.pipe_i));
	if (s->redir.rdr != NULL)
		free_tab((void ***)&s->redir.rdr, ft_tablen(s->redir.rdr));
	if (s->redir.cmd != NULL)
		free_tab((void ***)&s->redir.cmd, ft_tablen(s->redir.cmd));
	free_tab((void ***)&s->env_var, ft_tablen(s->env_var));
	free_tab((void ***)&s->shell_var, ft_tablen(s->shell_var));
	free_tab((void ***)&s->paths, ft_tablen(s->paths));
	free_tab((void ***)&s->argv, ft_tablen(s->argv));
	ft_strdel(&s->prompt);
	ft_exit();
	return (EXIT_SUCCESS);
}
