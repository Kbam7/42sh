/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:29:52 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/31 00:19:31 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

/*
execute_pipes(t_cmd_list *pipe_list, t_shell *s)
{
		while (pipe_list)
		{
//		printf("shell_loop() - pipe -- get_input(%s)\n", command->cmd); // debug
			get_input(pipe_list, s);

			if (s->input)

//		printf("shell_loop() - pipe -- execute_cmd(%s)\n", s->input[0]); // debug
			ret = execute_cmd(s, command->cmd);
			free_tab(s->input, ft_tablen(s->input));
			if (ret == EXIT_SH)
				break ;
			pipe_list = pipe_list->next;
		}
}

execute_redir(t_cmd_list *redir_list, t_shell *s)
{
		while (redir_list)
		{
			get_input()
//	printf("shell_loop() - pipe -- get_input(%s)\n", command->cmd); // debug
			get_input(command, s);
//	printf("shell_loop() - pipe -- execute_cmd(%s)\n", s->input[0]); // debug
			ret = execute_cmd(s, command->cmd);
			free_tab(s->input, ft_tablen(s->input));
		}
}
*/

void		shell_loop(t_shell *s)
{
	int			ret;
	t_cmd_list	*cmd_list;

	ret = 0;
	while (ret != EXIT_SH)
	{
		set_prompt(s);
		ft_putstr(s->prompt);
		if ((ret = get_commands(s) > 0)) // THIS MUST ONLY GET THE COMMANDS> It must not save any other list of pipes or redir. 
		{
printf("shell_loop() -- added cmd_list\n"); // debug
			cmd_list = s->commands;
			while (cmd_list != NULL) // ! end of cmd_list
			{
				ret = process_input(cmd_list, s); // this will run until all commands have been executed, "exit" was input, or there was an error.
				if (ret == EXIT_SH || ret == EXIT_FAILURE)
					break ;
//				free_tab(s->input, ft_tablen(s->input));
				cmd_list = cmd_list->next;
			}
print_cmd_list(s->commands); // debug
printf("shell_loop() -- free_cmd_list()\n"); // debug
			free_cmd_list(&s->commands);
		}
//		if ret == 0, nothin input
//		if ret < 0, gnl error gets printed, prompt is reprinted
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
