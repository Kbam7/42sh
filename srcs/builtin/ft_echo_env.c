/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:37:04 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 11:44:49 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_echo_env_check(char **new_str, char *temp, t_shell *s)
{
	int		i;
	char	**temp2;
	char	*temp3;

	i = 0;
	while (s->env_var[i])
	{
		if (ft_strncmp(s->env_var[i], ft_strjoin(temp, "="), \
					ft_strlen(temp) + 1) == 0)
		{
			temp2 = ft_strsplit(s->env_var[i], '=');
			if (*new_str != NULL)
				temp3 = ft_strjoin(*new_str, temp2[1]);
			else
				temp3 = temp2[1];
			if (*new_str)
				free(*new_str);
			*new_str = temp3;
		}
		i++;
	}
}

static int	ft_echo_local_env_check(char **new_str, char *temp, t_shell *s)
{
	int		i;
	char	**temp2;
	char	*temp3;
	int		found;

	i = 0;
	found = 0;
	while (s->shell_var[i])
	{
		if (ft_strncmp(s->shell_var[i], ft_strjoin(temp, "="), \
					ft_strlen(temp) + 1) == 0)
		{
			temp2 = ft_strsplit(s->shell_var[i], '=');
			if (*new_str != NULL)
				temp3 = ft_strjoin(*new_str, temp2[1]);
			else
				temp3 = temp2[1];
			if (*new_str)
				free(*new_str);
			*new_str = temp3;
			found = 1;
		}
		i++;
	}
	return (found);
}

void		ft_echo_env(char **new_str, char *str, int *flag, t_shell *s)
{
	int		i;
	char	*temp;

	i = 0;
	if (*flag == 0)
		*flag = -1;
	if (str[0] == '$' || str[1] == '$')
	{
		temp = ft_strsub(str, 1, ft_strlen(str) - 1);
		if (ft_echo_local_env_check(new_str, temp, s) == 0)
			ft_echo_env_check(new_str, temp, s);
		if (temp)
			free(temp);
	}
}
