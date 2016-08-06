/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:17 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 03:15:38 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*check_env_variables(char *name, t_shell *s)
{
	int		i;
	int		j;

	i = 0;
	while (s->env_var[i] != NULL)
	{
		j = 0;
		while (s->env_var[i][j] == name[j])
		{
			if (name[j + 1] == '\0' && s->env_var[i][j + 1] == '=')
				return (ft_strchr(s->env_var[i], '=') + 1);
			++j;
		}
		++i;
	}
	return (NULL);
}

char	*check_shell_variables(char *name, t_shell *s)
{
	int		i;
	int		j;

	i = 0;
	while (s->shell_var[i] != NULL)
	{
		j = 0;
		while (s->shell_var[i][j] == name[j])
		{
			if (name[j + 1] == '\0' && s->shell_var[i][j + 1] == '=')
				return (ft_strchr(s->shell_var[i], '=') + 1);
			++j;
		}
		++i;
	}
	return (NULL);
}

char	*ft_getenv(char *name, t_shell *s)
{
	char	*res;

	if (name)
	{
		if ((res = check_env_variables(name, s)) != NULL)
			return (res);
		else if ((res = check_shell_variables(name, s)) != NULL)
			return (res);	
	}
	return (NULL);
}
