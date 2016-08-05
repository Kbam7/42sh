/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 20:32:13 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/05 08:22:39 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	**ft_tabdup(char **tab, int len)
{
	int		i;
	char	**tmp;

	i = -1;
	if ((tmp = (char **)malloc(sizeof(char *) * (len + 1))) != NULL)
	{
		while (++i < len && tab[i])
			tmp[i] = ft_strdup(tab[i]);
		while (++i < len)
			tmp[i] = "\0";
		tmp[len] = NULL;
	}
	return (tmp);
}

int		ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		++i;
	return (i);
}

void	free_tab(void **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_memdel(&tab[i]);
		++i;
	}
	free(tab);
	tab = NULL;
}

char	**tab_trim(char **tab, int len)
{
	int		i;
	char	**trimmed;

	i = 0;
	if (len > 0)
	{
		trimmed = (char **)malloc(sizeof(char *) * len + 1);
		while (i < len)
		{
			trimmed[i] = ft_strtrim(tab[i]);
			++i;
		}
		return (trimmed);
	}
	return (tab);
}
