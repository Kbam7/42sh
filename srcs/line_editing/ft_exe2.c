/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 10:56:37 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 16:21:07 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    ft_path(t_shell *shell)
{
	char	**line;
	char	**line2;
	int		i;

	line2 = NULL;
	line = NULL;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
		{
			line2 = ft_strsplit(shell->env[i], '=');
			line = ft_strsplit(line2[1], ':');
			break ;
		}
		i++;
	}
    shell->path = ft_strdup_2(line);
	if (line2 != NULL)
	{
		ft_free_2(line2);
		ft_free_2(line);
		free(line2);
		free(line);
	}
}

int		ft_check_exec(char *path, char **args, t_shell *shell)
{
	char	*file;
	char	*temp;

	temp = ft_strjoin(path, "/");
	file = ft_strjoin(temp, args[0]);
	if (access(file, X_OK) != -1)
	{
		if (execve(file, args, shell->env) != -1)
			return (1);
	}
	free(file);
	free(temp);
	return (0);
}

int     ft_own_dir(char **args, t_shell *shell)
{
	if (access(args[0], X_OK) != -1)
		if (execve(args[0], args, shell->env) != -1)
			return (1);
	return (0);
}

int     ft_launch_own(char **args, t_shell *shell)
{
	pid_t   pid;
	pid_t   wpid;
	int     status;
	int     i;

	pid = fork();
	i = -1;
	if (pid == 0)
	{
			if (ft_own_dir(args, shell) == 1)
				exit (1);
		exit (10);
	}
	else
	{
		wait(&status);
		if (WEXITSTATUS(status) == 0)
			return (1);
	}
	return (0);
}

int		ft_launch(char **args, t_shell *shell)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int		i;

	pid = fork();
	i = -1;
	if (pid == 0)
	{
		while (shell->path[++i])
			if (ft_check_exec(shell->path[i], args, shell) == 1)
				exit (1);
		exit (10);
	}
	else
	{
		wait(&status);
		if (WEXITSTATUS(status) == 0)
			return (1);
	}
	return (0);
}
