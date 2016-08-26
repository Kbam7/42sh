/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 15:07:05 by tmack             #+#    #+#             */
/*   Updated: 2016/08/26 07:59:32 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2(char **c)
{
	int		i;

	i = 0;
	while (c[i] && c != NULL)
	{
		free(c[i]);
		c[i] = NULL;
		i++;
	}
	c = NULL;
}
