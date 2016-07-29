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
