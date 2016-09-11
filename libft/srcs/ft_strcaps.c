/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcaps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 12:12:21 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 12:05:22 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcaps(char *str)
{
	char			*new;
	int				i;
	int				len;

	i = 0;
	len = ft_strlen(str) + 1;
	new = (char *)malloc(sizeof(char) * len);
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			new[i] = ft_toupper(str[i]);
		else
			new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
