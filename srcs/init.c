/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 02:28:26 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/29 22:03:55 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	init_autocomplete_vars(t_shell *s)
{
	s->curr = NULL;
	s->tab_options = NULL;
	s->opt_i = 0;
	s->cmd_len = 0;
	s->cmd_fork = 0;
	s->tab_count = 0;
}

static void	init_builtin_func_options(t_shell *s)
{
	s->func_opt.env.u = 0;
	s->func_opt.env.i = 0;
	s->func_opt.echo.e = 0;
	s->func_opt.echo.up_e = 1;
	s->func_opt.echo.n = 0;
	s->func_opt.cd.l = 0;
	s->func_opt.cd.p = 1;
}

void		init_pipes_redirs(t_shell *s)
{
	s->pipe.pipes = NULL;
	s->pipe.n_pipes = 0;
	s->pipe.pipe_i = 0;
	s->redir.cmd = NULL;
	s->redir.nxt_cmd = NULL;
	s->redir.rdr = NULL;
	s->redir.n_rdr = 0;
	s->redir.rdr_i = 0;
	s->redir.pre_fd = -1;
	s->redir.post_fd = -1;
}

void		init_env(t_shell *s, int argc, char **argv, char **envp)
{
	t_split_string	tmp;
	char			*tmpstr;

	get_arg(argc, argv, s);
	init_builtin_func_options(s);
	s->env_var = ft_tabdup(envp, ft_tablen(envp));
	s->shell_var = ft_tabdup(envp, ft_tablen(envp));
	tmpstr = ft_getenv("PATH", s);
	tmp = ft_nstrsplit(tmpstr, ':');
	s->paths = ft_tabdup(tmp.strings, tmp.words);
	free_tab((void ***)&tmp.strings, tmp.words);
	s->prompt = ft_strnew(1);
	s->cwd = ft_getenv("PWD", s);
	s->commands = NULL;
	init_pipes_redirs(s);
	if (ft_getenv("42SH_PID", s) == NULL)
	{
		tmpstr = ft_itoa(getpid());
		ft_set(1, "42SH_PID", tmpstr, s);
		ft_strdel(&tmpstr);
	}
	init_autocomplete_vars(s);
}
