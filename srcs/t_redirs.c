/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 00:47:04 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 15:00:14 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	init_redir(char **rdr_str, char **cmd, t_shell *s)
{
	if (((s->redir.cmd = (char **)malloc(sizeof(char *) * 2)) == NULL) ||
				((s->redir.rdr = (char **)malloc(sizeof(char *) * 2)) == NULL))
	{
		ft_strdel(cmd);
		ft_strdel(rdr_str);
		return (err(ERR_MALLOC, "add_redir() -- init_redir()"));
	}
	else
	{
		s->redir.cmd[0] = !(*cmd) ? NULL : ft_strdup(*cmd);
		s->redir.cmd[1] = NULL;
		ft_strdel(cmd);
		s->redir.rdr[0] = !(*rdr_str) ? NULL : ft_strdup(*rdr_str);
		s->redir.rdr[1] = NULL;
		ft_strdel(rdr_str);
		s->redir.n_rdr++;
	}
	return (EXIT_SUCCESS);
}

static int	addto_redir(char **rdr_str, char **cmd, t_shell *s)
{
	char	**tmp;
	char	**tmp2;

	if (((tmp = ft_tabdup(s->redir.cmd, s->redir.n_rdr + 1)) == NULL) ||
				((tmp2 = ft_tabdup(s->redir.rdr, s->redir.n_rdr + 1)) == NULL))
	{
		ft_strdel(cmd);
		ft_strdel(rdr_str);
		return (err(ERR_MALLOC, "add_redir() -- ft_tabdup()"));
	}
	else
	{
		free_tab((void ***)&s->redir.cmd, ft_tablen(s->redir.cmd));
		s->redir.cmd = tmp;
		s->redir.cmd[s->redir.n_rdr] = !(*cmd) ? NULL : ft_strdup(*cmd);
		ft_strdel(cmd);
		free_tab((void ***)&s->redir.rdr, ft_tablen(s->redir.rdr));
		s->redir.rdr = tmp2;
		s->redir.rdr[s->redir.n_rdr] = !(*rdr_str) ? NULL : ft_strdup(*rdr_str);
		if (*rdr_str != NULL)
			s->redir.n_rdr++;
		ft_strdel(rdr_str);
	}
	return (EXIT_SUCCESS);
}

int			add_redir(char **rdr_str, char **cmd, t_shell *s)
{
	char	*trim;

	trim = *cmd;
	*cmd = ft_strtrim(trim);
	ft_strdel(&trim);
	if (s->redir.n_rdr == 0)
		return (init_redir(rdr_str, cmd, s));
	else if (s->redir.n_rdr > 0)
		return (addto_redir(rdr_str, cmd, s));
	return (EXIT_FAILURE);
}
