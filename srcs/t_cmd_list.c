#include "ft_shell.h"

t_cmd_list	*add_node(t_cmd_list *cmd_list, char *cmd)
{
	t_cmd_list	*node;
	t_cmd_list	*tmp;

	tmp = cmd_list;
	node = (t_cmd_list *)malloc(sizeof(node));
	if (node)
	{
		node->cmd = cmd;
		node->next = NULL;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (cmd_list);
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
		ft_strdel(cmd->cmd);
		free(cmd);
	}
}
