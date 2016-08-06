/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 00:47:04 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/06 01:24:29 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		add_redir(t_redirs **redirs, char *rdr_str, char *cmd)
{
	t_redirs	*new_redir;
	t_redirs	*tmp;
	
	tmp = *redirs;
	new_redir = (t_redirs *)malloc(sizeof(t_redirs));
	if (new_redir)
	{
		new_redir->rdr = rdr_str;
		new_redir->next = NULL;
		if (tmp != NULL)
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_redir;
		}
		else
			*redirs = new_redir;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	free_redirs(t_redirs **list)
{
	t_redirs	*redir;

	while (*list)
	{
		redir = *list;
		*list = (*list)->next;
		ft_strdel(&redir->redir);
		free(redir);
	}
}

void	print_redirs(t_redirs *list)
{
//printf("------- Printing Commands\n");
	t_redirs	*tmp;

	tmp = list;
	while (tmp)
	{
		printf(">%s\n", tmp->redir);
		tmp = tmp->next;
	}
//printf("------- FINISHED Printing Commands\n");
}
