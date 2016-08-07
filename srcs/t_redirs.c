/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 00:47:04 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/06 18:26:32 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int		init_redir(char *rdr_str, char *cmd, t_shell *s)
{
	if ((s->redir.cmd = (char **)malloc(sizeof(char *) * 2) == NULL)
		return (ERR_MALLOC, "add_redir() -- init_redir()");
	s->redir.cmd[0] = cmd;
	s->redir.cmd[1] = NULL;
	if ((s->redir.rdr = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (ERR_MALLOC, "add_redir() -- init_redir()");
	s->redir.rdr[0] = rdr_str;
	s->redir.rdr[1] = NULL;
	s->redir.n_rdr++;
	return (EXIT_SUCCESS);
}

int		add_redir(char *rdr_str, char *cmd, t_shell *s)
{
	char	**tmp;

	if (s->redir.n_rdr == 0)
		return(init_redir(rdr_str, cmd, s));
	else if (s->redir.n_rdr > 0)
	{
		if ((tmp = ft_tabdup(s->redir.cmd, s->redir.rdr_n) + 1) == NULL)
			return (err(ERR_MALLOC, "add_redir() -- ft_tabdup()"));
		free_tab(s->redir.cmd, ft_tablen(s->redir.cmd));
		s->redir.cmd = tmp;
		ft_strdel(&tmp);
		if ((tmp = ft_tabdup(s->redir.rdr, s->redir.rdr_n + 1) == NULL)
			return (err(ERR_MALLOC, "add_redir() -- ft_tabdup()"));
		free_tab(s->redir.rdr, ft_tablen(s->redir.rdr));
		s->redir.rdr = tmp;
		ft_strdel(&tmp);
		s->redir.n_rdr++;
		s->redir.rdr_i++;
		return(EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
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
			new_redir->n_rdr = tmp->n_rdr + 1;
			new_redir->rdr_i = tmp->rdr_i + 1;
			tmp->next = new_redir;
		}
		else
		{
			new_redir->n_rdr = 1;
			new_redir->rdr_i = 0;
			*redirs = new_redir;
		}
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
*/
