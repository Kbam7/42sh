/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 08:05:26 by tmack             #+#    #+#             */
/*   Updated: 2016/09/06 08:05:56 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	**ft_strdup_2(char **src)
{
	int		i;
	char	**new_dest;

	new_dest = NULL;
	i = 0;
	while (src[i])
		i++;
	new_dest = (char **)malloc(sizeof(char *) * (i + 1));
	ft_bzero(new_dest, i + 1);
	i = 0;
	while (src[i])
	{
		new_dest[i] = NULL;
		new_dest[i] = ft_strdup(src[i]);
		i++;
	}
	new_dest[i] = NULL;
	return (new_dest);
}
