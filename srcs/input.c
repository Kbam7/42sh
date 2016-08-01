/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/01 17:00:38 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	process_input(t_cmd_list *cmd, t_shell *s)
{
	int			error;

/*
				if ('|')	// if there is '|' in cmd
//					process_input(cmd_list->cmd, s);
				else if (!'|' && ('<' || '>') ) // if there is '>' or '<' in cmd. there will not be pipes in cmd.
//					execute_redir(cmd_list->redir);
*/			
	error = EXIT_FAILURE;
	if (ft_strchr(cmd->cmd, '|'))
		return (error);
	// return (process_pipes(cmd, s));
	else if (ft_strchr(cmd->cmd, '<') /*or '>'*/) // there will be no '|' in cmd
		return (error);
	// return (process_redirs(cmd, s));
	else
	{
		// cmd contains no operators, try and execute
		// check if is a file or a cmd
		// and execute, return output to s->output_fd
		get_input(cmd, s);
		error = execute_cmd(s);
		free_tab(s->input, ft_tablen(s->input));
	}
	return (error);
}

/*
int		process_pipe(t_cm_list *cmd, t_shell *s)
{
	t_split_string	pipes;
	size_t			i;

	i = 0;
	// split and use split[n - 1] as stdin for split[n] so that each pipe/cmd gets stdin from the pipe/cmd before it.
	pipes = ft_nstrsplit(cmd->cmd, '|');
	// cycle through split[] and process_input() each argument to check for redirs(< , >) or if can execute.
	while (pipes.strings[i] && i < pipes.words)
	{
		process_input(pipes.strings[i]);
		++i;
	}
	free_tab(pipes.strings[i], pipes.words);
}

int		process_redir(t_cmd_list *cmd, t_shell *s)
{
					// split. can separate by space ' '. All redirs will be separated by space, else error.
					// if is a redirect, found out which way it going and execute it with redir_input() or redir_output()

					//	if "<&-" or  ">&-"
					//	if '<', 
					//		split[n] is stdin for split[n - 1].
					// 		set_redirect(); // sets input and output fd.
					//	if '>',
					//		split[n] is stdin for split[n + 1].
					// 		set_redirect(); // sets input and output fd.
}
*/

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
