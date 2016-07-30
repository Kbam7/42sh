/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 18:53:31 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"
/*
static int	save_input(char *line, t_shell *s)
{
	char			*tmp;
	t_split_string	data;

	tmp = ft_strtrim(line);
	data = ft_nstrsplit(tmp, ' ');
	ft_strdel(&line);
	ft_strdel(&tmp);
	s->input = ft_tabdup(data.strings, data.words);
	free_tab(data.strings, data.words);
}
*/
static int	process_input(char *line, t_shell *s)
{
	int			error;
	t_cmd_list	*cmd;

/*
				if ('|')	// if there is '|' in cmd
//					process_input(cmd_list->cmd, s);
				else if (!'|' && ('<' || '>') ) // if there is '>' or '<' in cmd. there will not be pipes in cmd.
//					execute_redir(cmd_list->redir);
*/			
	error = EXIT_FAILURE;
	if (s->commands == NULL)
		return (/*store_commands()*/store_colon(line, s)
	if (ft_strchr(line, '|'))
	// execute_pipe()
					// split and use split[n - 1] as stdin for split[n] so that each pipe/cmd gets stdin from the pipe/cmd before it.
					// cycle through split[] and process_input() each argument to check for redirs(< , >).
	else if (ft_strchr(line, '<') /*or '>'*/) // there will be no '|' in line
	//	// execute_redir()
					// split. can separate by space ' '. All redirs will be separated by space, else error.
					// if is a redirect, found out which way it going and execute it with redir_input() or redir_output()

					//	if "<&-" or  ">&-"
					//	if '<', 
					//		split[n] is stdin for split[n - 1].
					// 		set_redirect(); // sets input and output fd.
					//	if '>',
					//		split[n] is stdin for split[n + 1].
					// 		set_redirect(); // sets input and output fd.

	else // line contains no operators.
				// check if is a file or a cmd
				// and execute, return output to s->output_fd
/*
	if (ft_strchr(cmd->cmd, '|'))
		error = store_pipe(&cmd);
//	else if (ft_strchr(cmd->cmd:, '<') || ft_strchr(cmd->cmd, '>'))
//		error = store_redirect(&cmd, s);
*/
}

int		get_commands(t_shell *s)
{
	char			*line;
	int				ret;
	char			*tmp;

	if ((ret = ft_gnl(0, &tmp)) > 0)
	{
		line = ft_strtrim(tmp);
		ft_strdel(&tmp);
		process_input(line, s);

//print_cmd_list(s->commands); // debug

		ft_strdel(&line);
	}
	if (ret < 0)
		ft_putstr_fd("ft_gnl Error!\n", 2);
	return (ret);
}

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
