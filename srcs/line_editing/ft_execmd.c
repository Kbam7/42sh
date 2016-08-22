/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 14:05:37 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 23:17:45 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	shorter(t_shell *s, char **commands)
{
	int     i;

	i = 0;
	if (commands[0] != NULL)
	{
		if (ft_strcmp(commands[0], "exit") == 0)
			exit(EXIT_SUCCESS); // ft_exit();
		else if (ft_strcmp(commands[0], "cd") == 0)
			i = ft_cd(commands, s);
		else if (ft_strcmp(commands[0], "env") == 0)
			ft_env(s, commands);
		else if (ft_strcmp(commands[0], "setenv") == 0)
			ft_setenv(s, commands);
		else if (ft_strcmp(commands[0], "unsetenv") == 0)
			ft_unsetenv(s, commands[1]);
		else if (ft_launch(commands, s) == 1)
			;
		else if (ft_launch_own(commands, s) == 1)
			;
		else
			ft_putendl("error, program not found");
	}
}

void	ft_execmd(t_shell *s)
{
	int		k;
	char	**commands;
	char	**semi;

	k = 0;
	semi = ft_semi(s);
	commands = NULL;
	while (k < s->line->nbr_semi)
	{
		commands = ft_strsplit(semi[k], ' ');
	ft_putendl(commands[0]);
		if (commands != NULL)
			shorter(s, commands);
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
