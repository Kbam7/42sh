/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 14:05:37 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 16:53:33 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	shorter(t_shell *shell, char **commands)
{
	int     i;

	i = 0;
	if (commands[0] != NULL)
	{
		if (ft_strcmp(commands[0], "exit") == 0)
			ft_exit();
		else if (ft_strcmp(commands[0], "cd") == 0)
			i = ft_cd(commands, shell);
		else if (ft_strcmp(commands[0], "env") == 0)
			ft_env(shell, commands);
		else if (ft_strcmp(commands[0], "setenv") == 0)
			ft_setenv(shell, commands);
		else if (ft_strcmp(commands[0], "unsetenv") == 0)
			ft_unsetenv(shell, commands[1]);
		else if (ft_launch(commands, shell) == 1)
			;
		else if (ft_launch_own(commands, shell) == 1)
			;
		else
			ft_putendl("error, program not found");
	}
}

void	ft_execmd(t_shell *shell)
{
	int		k;
	char	**commands;
	char	**semi;

	k = 0;
	semi = ft_semi(shell);
	commands = NULL;
	while (k < shell->nbr_semi)
	{
		commands = ft_strsplit(semi[k], ' ');
	ft_putendl(commands[0]);
		if (commands != NULL)
			shorter(shell, commands);
		if (commands != NULL)
		{
			ft_free_2(commands);
			free(commands);
		}
		k++;
	}
	if (semi != NULL)
		ft_free_2(semi);
	free(semi);
}
