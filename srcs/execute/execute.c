/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 13:29:03 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	make_path_and_execute(char *path, t_shell *s)
{
	int				i;
	char			*tmp;
	t_split_string	sp;

	i = -1;
	sp = ft_nstrsplit(path, ':');
	if (s->paths)
		free_tab((void ***)&s->paths, ft_tablen(s->paths));
	s->paths = ft_tabdup(sp.strings, sp.words);
	free_tab((void ***)&sp.strings, sp.words);
	while (s->paths[++i] != NULL)
	{
		tmp = ft_strjoinstr(s->paths[i], "/", s->input[0]);
		if (access(tmp, F_OK) == 0)
			if (check_rights(tmp, 'r', 0, 'x') == EXIT_SUCCESS)
				if (execve(tmp, s->input, s->env_var) != -1)
				{
					ft_strdel(&tmp);
					free_t_shell(s);
				}
		ft_strdel(&tmp);
	}
}

static int	try_system(t_shell *s)
{
	char	*tmp;

	if (access(s->input[0], F_OK) == 0)
	{
		if (check_rights(s->input[0], 'r', 0, 'x') == EXIT_SUCCESS)
			if (execve(s->input[0], s->input, s->env_var) != -1)
				free_t_shell(s);
	}
	else if ((tmp = ft_getenv("PATH", s)))
		make_path_and_execute(tmp, s);
	return (ERR_NOTFOUND);
}

int			ft_execute(t_shell *s)
{
	int i;

	if (s->pipe.n_pipes)
		child_pipe(s);
	if (s->redir.n_rdr)
	{
		i = s->redir.rdr_i;
		if (s->redir.dir == '>')
			child_output_redir(s->redir.rdr[i], s);
		else if (s->redir.dir == '<')
			child_input_redir(s->redir.rdr[i], s);
	}
	if ((i = try_child_builtin(s)) == ERR_NOTFOUND)
		i = try_system(s);
	return (i);
}

int			execute_cmd(t_shell *s)
{
	pid_t	pid;
	int		st;

	st = EXIT_FAILURE;
	if ((st = try_parent_builtin(s)) == ERR_NOTFOUND)
	{
		if (s->pipe.n_pipes)
			st = ft_execute(s);
		else
		{
			if ((pid = fork()) < 0)
				return (err(ERR_FORK_FAILED, ""));
			if (pid == 0)
			{
				if (s->fork_pid != 0)
	        	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	        	tputs(tgetstr("cd", 0), 1, ft_putchar_re);
				st = ft_execute(s);
				free_t_shell(s);
				exit(st == 0 ? 0 : (st - 900));
			}
			wait(&st);
			if (WIFEXITED(st) && (st = WEXITSTATUS(st)) != EXIT_SUCCESS)
				return (err(((st == 1) ? 1 : st + 900), s->input[0]));
		}
	}
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	return (st);
}
