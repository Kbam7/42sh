/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/30 13:31:48 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 20:26:12 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		add_cmd(t_cmd_list **cmd_list, char *cmd)
{
	t_cmd_list	*new_cmd;
	t_cmd_list	*tmp;
	static int i = 0;
	
	tmp = *cmd_list;
	new_cmd = (t_cmd_list *)malloc(sizeof(new_cmd));
	if (new_cmd)
	{
//i++; // debug
//ft_printf("%d - add_cmd(%s)\n", i, cmd); // debug

		new_cmd->cmd = ft_strdup(cmd); // NOTE!! check if ft_strdup returns successfully
		new_cmd->pipes = NULL;
		new_cmd->redir = NULL;
		new_cmd->next = NULL;
		if (tmp != NULL)
		{
//ft_putstr("add_cmd --  list not empty\n"); // debug
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_cmd;
//ft_putstr("add_cmd --  new_cmd assigned\n"); // debug
		}
		else
		{
//ft_putstr("add_cmd --  list empty\n"); // debug
			*cmd_list = new_cmd;
//ft_putstr("add_cmd --  new_cmd assigned\n"); // debug
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}



void	free_cmd_list(t_cmd_list **list)
{
	t_cmd_list	*cmd;

	while (*list)
	{

ft_putstr("Here free_cmd_list -- 1\n"); // debug

		cmd = *list;
		*list = (*list)->next;

ft_putstr("Here free_cmd_list -- 2\n"); // debug

		if (cmd->pipes)
			free_cmd_list(&cmd->pipes);
		if (cmd->redir)
			free_cmd_list(&cmd->redir);

ft_putstr("Here free_cmd_list -- 3\n"); // debug

		ft_strdel(&cmd->cmd);
		free(cmd);
	}
}

void	print_cmd_list(t_cmd_list *list)
{
printf("------- Printing Commands\n");
	while (list)
	{
		printf(">%s\n", list->cmd);
		list = list->next;
	}
printf("------- FINISHED Printing Commands\n");
}
