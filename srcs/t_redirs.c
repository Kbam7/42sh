/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 00:47:04 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/09 21:01:43 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	init_redir(char *rdr_str, char *cmd, t_shell *s)
{
	if ((s->redir.cmd = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (err(ERR_MALLOC, "add_redir() -- init_redir()"));
	s->redir.cmd[0] = cmd;
	s->redir.cmd[1] = NULL;
	if ((s->redir.rdr = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (err(ERR_MALLOC, "add_redir() -- init_redir()"));
	s->redir.rdr[0] = rdr_str;
	s->redir.rdr[1] = NULL;
	s->redir.n_rdr++;
	return (EXIT_SUCCESS);
}

int			add_redir(char *rdr_str, char *cmd, t_shell *s)
{
	char	**tmp;

	// check if rdr_string contains two '&', if it does, then error
	if (ft_strchr(ft_strchr(rdr_str, '&'), '&'))
		return (EXIT_FAILURE);
	if (s->redir.n_rdr == 0)
		return (init_redir(rdr_str, cmd, s));
	else if (s->redir.n_rdr > 0)
	{
		if ((tmp = ft_tabdup(s->redir.cmd, s->redir.n_rdr + 1)) == NULL)
			return (err(ERR_MALLOC, "add_redir() -- ft_tabdup()"));
		free_tab((void **)s->redir.cmd, ft_tablen(s->redir.cmd));
		s->redir.cmd = tmp;
		s->redir.cmd[s->redir.n_rdr] = cmd;
		if ((tmp = ft_tabdup(s->redir.rdr, s->redir.n_rdr + 1)) == NULL)
			return (err(ERR_MALLOC, "add_redir() -- ft_tabdup()"));
		free_tab((void **)s->redir.rdr, ft_tablen(s->redir.rdr));
		s->redir.rdr = tmp;
		s->redir.rdr[s->redir.n_rdr] = rdr_string;
		s->redir.n_rdr++;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
