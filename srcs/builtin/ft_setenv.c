/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:47 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/14 18:51:05 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	new_env_var(char *name, char *value, char ***env)
{
	char	**tab;
	char	*tmp;
	int		len;

	len = ft_tablen(*env);
	tab = ft_tabdup(*env, len + 1);
	free_tab((void ***)env, len);
	tmp = ft_strjoin("=", value);
	tab[len] = ft_strjoin(name, tmp);
	ft_strdel(&tmp);
	*env = tab;
	return (EXIT_SUCCESS);
}

static int	variable_exists(char *name, char *value, char ***env)
{
	int				i;
	char			*tmp;
	t_split_string	tab;

	i = 0;
	while ((*env)[i] != NULL)
	{
		tab = ft_nstrsplit((*env)[i], '=');
		if (ft_strcmp(name, tab.strings[0]) == 0)
		{
			ft_strdel(&(*env)[i]);
			tmp = ft_strjoin("=", value);
			(*env)[i] = ft_strjoin(name, tmp);
			ft_strdel(&tmp);
			free_tab((void ***)&tab.strings, tab.words);
			return (EXIT_SUCCESS);
		}
		free_tab((void ***)&tab.strings, tab.words);
		++i;
	}
	return (EXIT_FAILURE);
}

static int	ft_set_env(char *name, char *value, char ***env)
{
	if (variable_exists(name, value, env) == EXIT_FAILURE)
		if (new_env_var(name, value, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	get_and_set_values(char *str, char ***env)
{
	t_split_string	args;
	int				status;

	status = EXIT_FAILURE;
	args = ft_nstrsplit(str, '=');
	if (args.words > 2 || args.words < 1)
		return (err(ERR_INVALID_ARG, "set"));
	if (args.words == 1)
		status = ft_set_env(args.strings[0], "", env);
	else
		status = ft_set_env(args.strings[0], args.strings[1], env);
	free_tab((void ***)&args.strings, args.words);
	return (status);
}

int			ft_set(int env_type, char *name, char *val, t_shell *s)
{
	int				status;
	char			***env;

	status = EXIT_FAILURE;
	env = check_env_type(env_type, s);
	if (!name && !val)
		print_variables(*env);
	else if (name && ft_strchr(name, '='))
		status = get_and_set_values(name, env);
	else if (val && ft_strchr(val, '='))
		status = get_and_set_values(val, env);
	else if (name && val)
		status = ft_set_env(name, val, env);
	else if (name && !val)
		status = ft_set_env(name, "", env);
	else if (val && !name)
		status = ft_set_env(val, "", env);
	else
		return (err(ERR_INVALID_ARG, "set"));
	if (env_type == 1)
		status = ft_set(2, name, val, s);
	return (status);
}
