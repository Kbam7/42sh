/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 13:32:12 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 23:15:25 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_env(t_shell *s, char **command)
{
	int		i;

	i = 0;
	if (command[1] == NULL)
		while (s->line->env[i])
		{
			ft_putstr(s->line->env[i++]);
			ft_putchar('\n');
		}
	else if (ft_strcmp(command[1], "-i") == 0)
	{
		ft_free_2(s->line->env);
		s->line->env[i] = NULL;
	}
	else if (ft_strcmp(command[1], "-u") == 0)
		ft_unsetenv(s, command[2]);
}

void	ft_unsetenv(t_shell *s, char *commands)
{
	char	**newenv;
	int		last;
	int		i;
	int		j;

	i = -1;
	j = -1;
	last = ft_nbr_y(s->line->env);
	while (commands[++i] != '\0')
		if (commands[i] == '=')
		{
			ft_putendl("cant use =");
			return ;
		}
	i = -1;
	newenv = (char **)malloc(sizeof(char *) * (last + 1));
	while (s->line->env[++i] != NULL)
		if (ft_strncmp(commands, s->line->env[i], ft_strlen(commands)) != 0)
			newenv[++j] = ft_strdup(s->line->env[i]);
	newenv[j + 1] = NULL;
	ft_free_2(s->line->env);
	free(s->line->env);
	s->line->env = ft_strdup_2(newenv);
	ft_free_2(newenv);
	free(newenv);
}

int		ft_setenvi_short(char **newenv, char **commands, char *temp)
{
	int		i;

	i = -1;
	while (newenv[++i])
		if (ft_strncmp(newenv[i], commands[1], ft_strlen(commands[1])) == 0)
		{
			ft_memdel((void *)&newenv[i]);
			newenv[i] = ft_strdup(temp);
			break ;
		}
	return (i);
}

void	ft_setenv(t_shell *s, char **commands)
{
	char	**newenv;
	int		last;
	int		i;
	char	*temp;
	char	*temp1;

	i = -1;
	temp1 = ft_strjoin(commands[1], "=");
	temp = ft_strjoin(temp1, commands[2]);
	last = ft_nbr_y(s->line->env);
	newenv = (char **)malloc(sizeof(char *) * (last + 2));
	while (s->line->env[++i])
		newenv[i] = ft_strdup(s->line->env[i]);
	newenv[i] = NULL;
	i = ft_setenvi_short(newenv, commands, temp);
	if (i == last)
		newenv[last] = ft_strdup(temp);
	newenv[i + 1] = NULL;
	ft_free_2(s->line->env);
	free(s->line->env);
	s->line->env = ft_strdup_2(newenv);
	free(temp);
	free(temp1);
	ft_free_2(newenv);
	free(newenv);
}
