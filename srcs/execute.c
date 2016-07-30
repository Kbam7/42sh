/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 00:46:38 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	try_builtin(t_shell *s)
{
	if (ft_strcmp(s->input[0], "cd") == 0)
		return (ft_cd(s->input, s));
	else if (ft_strcmp(s->input[0], "echo") == 0)
		return (ft_echo(s->input, s));
	else if (ft_strcmp(s->input[0], "21sh") == 0)
		return (run_shell(s));
	else if (ft_strcmp(s->input[0], "env") == 0)
		return (ft_env(s->input, s));
//	else if (ft_strcmp(s->input[0], "printenv") == 0)
//		return (ft_env(s));
	else if (ft_strcmp(s->input[0], "set") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "setenv") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "export") == 0)
		return (ft_set(1, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "unsetenv") == 0)
		return (ft_unsetenv(s->input[1], s));
	else if (ft_strcmp(s->input[0], "unset") == 0)
		return (ft_unsetenv(s->input[1], s));
	else
		return (ft_strcmp(s->input[0], "exit") == 0 ? EXIT_SH : ERR_NOTFOUND);
}

int		try_system(t_shell *s)
{
	int		i;
	char	*path;
	char	**var;

	i = 0;
	var = (ft_strcmp(s->input[0], "printenv") == 0) ?
													s->env_var : s->shell_var;
	while (s->paths[i] != NULL)
	{
		path = ft_nstrjoin(s->paths[i], "/", s->input[0]);
		if (access(path, F_OK) == 0)
			if (check_rights(path, 'r', 0, 'x') == EXIT_SUCCESS)
			{
				if (execve(path, s->input, var) != -1)
					ft_strdel(&path);
				exit(EXIT_SUCCESS);
			}
		ft_strdel(&path);
		++i;
	}
	free_tab(s->input, ft_tablen(s->input));
	free_t_shell(s);
	exit(EXIT_FAILURE);
}

int		execute_cmd(t_shell *s)
{
	pid_t	pid;
	int		status;

	status = EXIT_FAILURE;
	if ((status = try_builtin(s)) == ERR_NOTFOUND)
	{
		pid = fork();
		if (pid < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
			try_system(s);
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == EXIT_FAILURE)
			err(ERR_NOTFOUND, s->input[0]);
	}
	return (status);
}
