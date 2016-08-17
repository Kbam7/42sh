/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redirs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 00:47:04 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/17 11:20:10 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	init_redir(char **rdr_str, char **cmd, t_shell *s)
{

dprintf(1, "add_redir() - init_redir() -- "
			"adding rdr_str = >%s<\tadding cmd = >%s<\n", *rdr_str, *cmd); // debug

	if ((s->redir.cmd = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (err(ERR_MALLOC, "add_redir() -- init_redir(cmd)"));
	s->redir.cmd[0] = !(*cmd) ? NULL : ft_strdup(*cmd);
	s->redir.cmd[1] = NULL;
	ft_strdel(cmd);
	if ((s->redir.rdr = (char **)malloc(sizeof(char *) * 2)) == NULL)
		return (err(ERR_MALLOC, "add_redir() -- init_redir(rdr)"));
	s->redir.rdr[0] = !(*rdr_str) ? NULL : ft_strdup(*rdr_str);
	s->redir.rdr[1] = NULL;
	ft_strdel(rdr_str);
// setup pipe for this redir
//	if ((s->redir.pipe = (int **)malloc(sizeof(int *) * 2)) == NULL)
//		return (err(ERR_MALLOC, "add_redir() -- init_redir(pipe)"));
//	if ((s->redir.pipe[0] = (int *)malloc(sizeof(int) * 2)) == NULL)
//		return (err(ERR_MALLOC, "add_redir() -- init_redir(pipe)"));
//	if ((pipe(s->redir.pipe[0]) == -1))
//		return (err(ERR_CREATE_PIPE, "add_redir() -- init_redir()"));
//	s->redir.pipe[1] = NULL;

	s->redir.n_rdr++;

dprintf(1, "add_redir() - init_redir() -- Finished adding redir\n");

	return (EXIT_SUCCESS);
}

static int	addto_redir(char **rdr_str, char **cmd, t_shell *s)
{
	char	**tmp;
//	int		**new_pipe;

dprintf(1, "add_redir() - addto_redir() - redir list exists, adding redir -- "
			"rdr_str = >%s<\tcmd = >%s<\n", *rdr_str, *cmd); // debug

// cmds
	if ((tmp = ft_tabdup(s->redir.cmd, s->redir.n_rdr + 1)) == NULL)
		return (err(ERR_MALLOC, "add_redir() -- ft_tabdup()"));
	free_tab((void ***)&s->redir.cmd, ft_tablen(s->redir.cmd));
	s->redir.cmd = tmp;
	s->redir.cmd[s->redir.n_rdr] = !(*cmd) ? NULL : ft_strdup(*cmd);
	ft_strdel(cmd);
// redirs
	if ((tmp = ft_tabdup(s->redir.rdr, s->redir.n_rdr + 1)) == NULL)
		return (err(ERR_MALLOC, "add_redir() -- ft_tabdup()"));
	free_tab((void ***)&s->redir.rdr, ft_tablen(s->redir.rdr));
	s->redir.rdr = tmp;
	s->redir.rdr[s->redir.n_rdr] = !(*rdr_str) ? NULL : ft_strdup(*rdr_str);
	ft_strdel(rdr_str);
	if (*rdr_str != NULL)
		s->redir.n_rdr++;
// pipes
//	if (*rdr_str != NULL)
//	{
//		if ((new_pipe = ft_pipedup(s->redir.pipe, s->redir.n_rdr + 1)) == NULL)
//			return (err(ERR_MALLOC, "add_redir() -- ft_pipedup()"));
//		free_pipes(&s->redir.pipe, s->redir.n_rdr + 1);
//		s->redir.pipe = new_pipe;
//		if ((pipe(s->redir.pipe[s->redir.n_rdr]) == -1)) // init new pipe
//			return (err(ERR_CREATE_PIPE, "add_redir()"));
//dprintf(1, "add_redir() - addto_redir() -- Made pipe for '%s'\n", *rdr_str);

dprintf(1, "add_redir() - Finished adding redir\n");

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
