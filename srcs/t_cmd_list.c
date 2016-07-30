/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/30 13:31:48 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 13:34:58 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		add_cmd(t_cmd_list **cmd_list, char *cmd)
{
	t_cmd_list	*new_cmd;
	t_cmd_list	*tmp;
	
	tmp = *cmd_list;
	new_cmd = (t_cmd_list *)malloc(sizeof(new_cmd));
	if (new_cmd)
	{

ft_putstr("Here\n");

		new_cmd->cmd = ft_strdup(cmd);
		new_cmd->pipes = NULL;
		new_cmd->redir = NULL;
		new_cmd->next = NULL;
		if (tmp != NULL)
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_cmd;
		}
		else
			*cmd_list = new_cmd;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}



void	free_cmd_list(t_cmd_list **list)
{
	t_cmd_list	*cmd;

	while (*list)
	{
		cmd = *list;
		*list = (*list)->next;
		if (cmd->pipes)
			free_cmd_list(&cmd->pipes);
		if (cmd->redir)
			free_cmd_list(&cmd->redir);
		ft_strdel(&cmd->cmd);
		free(cmd);
	}
}
