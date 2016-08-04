/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 02:28:26 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/04 18:01:45 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

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

void	init_env(t_shell *s, int argc, char **argv, char **envp)
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
	free_tab((void **)tmp.strings, tmp.words);
	if (ft_getenv("21SH_PATH", s) == NULL)
	{
		tmpstr = ft_strjoin(ft_getenv("PWD", s), ft_strchr(argv[0], '/'));
		ft_set(1, "21SH_PATH", tmpstr, s);
		ft_strdel(&tmpstr);
	}
	s->prompt = ft_strnew(1);
	s->cwd = ft_getenv("PWD", s);
	s->commands = NULL;

// pipes, redirs and fd's

//dprintf(2, "init() -- s->read_fd(OLD) = UNINITIALIZED\n"); // debug
//	dup2(STDIN_FILENO, s->read_fd);
//	s->read_fd = dup(STDIN_FILENO);
//dprintf(2, "init() -- s->read_fd(NEW) = %d -- STDIN_FILENO = %d\n", s->read_fd, STDIN_FILENO); // debug
//dprintf(2, "init() -- s->write_fd(OLD) = UNINITIALIZED\n"); // debug
//	dup2(STDOUT_FILENO, s->write_fd);
//	s->write_fd = dup(STDOUT_FILENO);
//dprintf(2, "init() -- s->write_fd(NEW) = %d -- STDOUT_FILENO = %d\n", s->write_fd, STDOUT_FILENO); // debug
	s->pipes = NULL;
	s->n_pipes = 0;
	s->pipe_i = 0;
	s->redirs = NULL;
	s->n_redirs = 0;
	s->redir_i = 0;

}
