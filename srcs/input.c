/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 21:47:06 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		get_commands(t_shell *s)
{
	char			*cmd;
	int				ret;
	char			*tmp;

	if ((ret = ft_gnl(0, &tmp)) > 0)
	{
		cmd = ft_strtrim(tmp);
		ft_strdel(&tmp);
		if (store_commands(cmd, s) != EXIT_SUCCESS)
		{
			ft_strdel(&cmd);
			return (0);
		}

ft_printf("Here -------------\n");

print_cmd_list(s->commands); // debug

ft_printf("Here -------------\n");

		ft_strdel(&cmd);

ft_printf("Here -------------\n");

	}
	if (ret < 0)
		return (err(ERR_GNL, "ft_gnl Error!"));
	return (ret);
}

// This will get the string of the command and make it into input[](argv for executing commands)
void	get_input(t_cmd_list *command, t_shell *s)
{
	char			*tmp;
	t_split_string	data;

	tmp = ft_strtrim(command->cmd);
	data = ft_nstrsplit(tmp, ' ');
	ft_strdel(&tmp);
	s->input = ft_tabdup(data.strings, data.words);
	free_tab(data.strings, data.words);
}

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
