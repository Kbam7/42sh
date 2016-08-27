/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:27:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/27 02:32:28 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	remove_var(char *name, char **var)
{
	char			**tmp;
	int				i;
	t_split_string	data;

	i = 0;
	while (var[i] != NULL)
	{
		data = ft_nstrsplit(var[i], '=');
		if (ft_strcmp(name, data.strings[0]) == 0)
		{
			ft_strdel(&var[i]);
			while (var[++i] != NULL)
				var[i - 1] = var[i];
			tmp = ft_tabdup(var, ft_tablen(var));
			free_tab((void ***)&var, ft_tablen(var));
			var = ft_tabdup(tmp, ft_tablen(tmp));
			free_tab((void ***)&tmp, ft_tablen(tmp));
			free_tab((void ***)&data.strings, data.words);
			break ;
		}
		free_tab((void ***)&data.strings, data.words);
		++i;
	}
}

int			ft_unsetenv(char *name, t_shell *s)
{
	if (name == NULL || ft_strchr(name, '='))
		return (err(ERR_INVALID_ARG, "unsetenv"));
	if (check_env_variables(name, s) != NULL)
		remove_var(name, s->env_var);
	if (check_shell_variables(name, s) != NULL)
		remove_var(name, s->shell_var);
	return (EXIT_SUCCESS);
}
