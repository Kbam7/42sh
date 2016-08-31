/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:27:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/31 22:13:37 by kbamping         ###   ########.fr       */
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
dprintf(2, "ft_unsetenv() - remove_var() -- MOVE i(%d) -to i-1(%d) -- '%s' -to- '%s'\n", i, i-1, (*var)[i], (*var)[i- 1]); // debug
		(*var)[i - 1] = ft_strdup((*var)[i]);
		ft_strdel(&(*var)[i]);
	}
//	(*var)[i] = NULL;
dprintf(2, "ft_unsetenv() - remove_var() --  tadup(var) tablen(var) = '%d'\n", ft_tablen(*var)); // debug
	tmp = ft_tabdup(*var, ft_tablen(*var));
	free_tab((void ***)var, ft_tablen(*var));
	*var = tmp;
}

static void	remove_var(char *name, char ***var)
{
	int				i;
	t_split_string	data;

dprintf(2, "ft_unsetenv() - remove_var() -- START -- ft_tablen(var) = '%d'\n", ft_tablen(*var)); // debug

	i = 0;
	while ((*var)[i] != NULL)
	{
dprintf(2, "ft_unsetenv() - remove_var() -- Loop '%d' checking '%s'\n", i, (*var)[i]); // debug
		data = ft_nstrsplit((*var)[i], '=');
		if (ft_strcmp(name, data.strings[0]) == 0)
		{
			free_tab((void ***)&data.strings, data.words);
dprintf(2, "ft_unsetenv() - remove_var() -- removing '%s'\n", (*var)[i]); // debug
			delete_var(var, i);
//			free((*var)[i]);
/*
			ft_strdel(&(*var)[i]);
			while ((*var)[i + 1] != NULL)
			{
				++i;
dprintf(2, "ft_unsetenv() - remove_var() -- MOVE i(%d) -to i-1(%d) -- '%s' -to- '%s'\n", i, i-1, (*var)[i], (*var)[i- 1]); // debug
				(*var)[i - 1] = (*var)[i];
			}
//			(*var)[i] = NULL;
dprintf(2, "ft_unsetenv() - remove_var() --  tadup(var) tablen(var) = '%d'\n", ft_tablen(*var)); // debug
			tmp = ft_tabdup(*var, ft_tablen(*var));
			free_tab((void ***)var, ft_tablen(*var));
			*var = tmp;
*/
		}
		else
		{
			free_tab((void ***)&data.strings, data.words);
			++i;
		}
	}

dprintf(2, "ft_unsetenv() - remove_var() -- END\n"); // debug
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
