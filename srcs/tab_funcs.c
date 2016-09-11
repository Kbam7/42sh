/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 20:32:13 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 14:52:31 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	**ft_tabnew(char *str, size_t len)
{
	char	**new_str;
	size_t	i;

	if ((new_str = (char **)ft_memalloc(sizeof(char *) * (len + 1))) == NULL)
		return (err(ERR_MALLOC, "ft_tabnew()") ? NULL : NULL);
	if (str == NULL)
		new_str[0] = NULL;
	else
		new_str[0] = ft_strdup(str);
	i = 0;
	while (++i <= len)
		new_str[i] = NULL;
	return (new_str);
}

char	**ft_tabdup(char **table, int len)
{
	int		i;
	char	**tmp;

	i = -1;
	if ((tmp = (char **)malloc(sizeof(char *) * (len + 1))) != NULL)
	{
		while (++i < len && table[i])
			tmp[i] = ft_strdup(table[i]);
		while (++i < len)
			tmp[i] = "\0";
		tmp[len] = NULL;
	}
	return (tmp);
}

int		ft_tablen(char **table)
{
	int	i;

	i = 0;
	while (table[i] != NULL)
		++i;
	return (i);
}

void	free_tab(void ***table, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_memdel(&(*table)[i]);
		++i;
	}
	free(*table);
	*table = NULL;
}

char	**tab_trim(char **table, int len)
{
	int		i;
	char	**trimmed;

	i = 0;
	if (len > 0)
	{
		trimmed = (char **)ft_memalloc(sizeof(char *) * len + 1);
		while (i < len)
		{
			trimmed[i] = ft_strtrim(table[i]);
			++i;
		}
		return (trimmed);
	}
	return (table);
}
