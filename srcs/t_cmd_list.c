/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/30 13:31:48 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/09 00:56:00 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		add_cmd(t_cmd_list **cmd_list, char *cmd)
{
	t_cmd_list	*new_cmd;
	t_cmd_list	*tmp;

	tmp = *cmd_list;
	new_cmd = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (new_cmd)
	{
		if ((new_cmd->cmd = ft_strdup(cmd)) == NULL)
		{
			err(ERR_MALLOC, "add_cmd()");
			return (EXIT_FAILURE);
		}
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
		ft_strdel(&cmd->cmd);
		free(cmd);
	}
}

void	print_cmd_list(t_cmd_list *list)
{
	t_cmd_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf(">%s\n", tmp->cmd);
		tmp = tmp->next;
	}
}
