/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 13:26:34 by kbamping         ###   ########.fr       */
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

	error = EXIT_FAILURE;
	cmd = s->commands;
	while (cmd != NULL)
	{
		if (ft_strchr(cmd->cmd, '|'))
			error = check_pipe(&cmd);
//		else if (ft_strchr(cmd->cmd:, '<') || ft_strchr(cmd->cmd, '>'))
//			error = check_redirect(&cmd, s);
		cmd = cmd->next;
	}
	if (s->commands == NULL)
	{
		if ((error = check_colon(line, s)) != EXIT_SUCCESS)
			return (error);
		return (process_input(line, s));
	}
	return (error);
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
