/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:27:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 12:49:51 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	delete_var(char ***var, int i)
{
	char			**tmp;

	ft_strdel(&(*var)[i]);
	while ((*var)[i + 1] != NULL)
	{
		++i;
		(*var)[i - 1] = ft_strdup((*var)[i]);
		ft_strdel(&(*var)[i]);
	}
	tmp = ft_tabdup(*var, ft_tablen(*var));
	free_tab((void ***)var, ft_tablen(*var));
	*var = tmp;
}

static void	remove_var(char *name, char ***var)
{
	int				i;
	t_split_string	data;

	i = 0;
	while ((*var)[i] != NULL)
	{
		data = ft_nstrsplit((*var)[i], '=');
		if (ft_strcmp(name, data.strings[0]) == 0)
			delete_var(var, i);
		else
			++i;
		free_tab((void ***)&data.strings, data.words);
	}
}

int			ft_unsetenv(char *name, t_shell *s)
{
	if (name == NULL || ft_strchr(name, '='))
		return (err(ERR_INVALID_ARG, "unsetenv"));
	if (check_env_variables(name, s) != NULL)
		remove_var(name, &s->env_var);
	if (check_shell_variables(name, s) != NULL)
		remove_var(name, &s->shell_var);
	return (EXIT_SUCCESS);
}
