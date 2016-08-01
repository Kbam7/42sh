/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/30 23:16:38 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/01 17:00:38 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	store_commands(char *str, t_shell *s)
{
	size_t			i;
	int				ret;
	t_split_string	args;

	i = 0;
	ret = EXIT_FAILURE;
	if (ft_strchr(str, ';'))
	{
		args = ft_nstrsplit(str, ';');
		while (i < args.words)
		{
			ret = add_cmd(&s->commands, args.strings[i]);
			++i;
		}
		free_tab(args.strings, args.words);
	}
	else
		ret = add_cmd(&s->commands, str);
	return (ret);
}

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
		ft_strdel(&cmd);
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
/*
int	store_pipe(t_cmd_list **cmd)
{
	size_t			i;
	int				ret;
	t_split_string	args;
	t_cmd_list		*pipes;

	i = 0;
	args = ft_nstrsplit((*cmd)->cmd, '|');
	if (args.words > 1)
	{
		while (i < args.words)
		{
			ret = add_cmd(&(*cmd)->pipes, args.strings[i]);
			++i;
		}
		return (ret);
	}
	else
		return (err(ERR_INVALID_PIPE, "--- store_pipe()---"));
}
*/
/*
int	store_redirect(t_cmd_list *cmd, t_shell *s)
{
	int	i;

	i = 0;
	while (cmd->cmd[i] != '\0')
	{
		if (cmd->cmd[i] == '>')
			store_write
		if (cmd->cmd[i] == '<')
		
	}
}
*/
