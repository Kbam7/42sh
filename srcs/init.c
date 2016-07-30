/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 02:28:26 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 02:17:41 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	init_func_options(t_shell *s)
{
	s->func_opt.env.u = 0;
	s->func_opt.env.i = 0;
	s->func_opt.echo.e = 0;
	s->func_opt.echo.up_e = 1;
	s->func_opt.echo.n = 0;
	s->func_opt.cd.l = 0;
	s->func_opt.cd.p = 1;
}

void	init_env(t_shell *s, int argc, char **argv, char **envp)
{
	t_split_string	tmp;
	char			*tmpstr;

	init_func_options(s);
	s->env_var = ft_tabdup(envp, ft_tablen(envp));
	s->shell_var = ft_tabdup(envp, ft_tablen(envp));
	tmpstr = ft_getenv("PATH", s);
	tmp = ft_nstrsplit(tmpstr, ':');
	s->paths = ft_tabdup(tmp.strings, tmp.words);
	free_tab(tmp.strings, tmp.words);
	if (ft_getenv("21SH_PATH", s) == NULL)
	{
		tmpstr = ft_strjoin(ft_getenv("PWD", s), ft_strchr(argv[0], '/'));
		ft_set(1, "21SH_PATH", tmpstr, s);
		ft_strdel(&tmpstr);
	}
	s->prompt = ft_strnew(1);
	s->cwd = ft_getenv("PWD", s);
	get_arg(argc, argv, s);
	s->commands = NULL;
}
