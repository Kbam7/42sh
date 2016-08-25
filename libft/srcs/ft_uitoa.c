/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 12:50:26 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/15 13:00:15 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_uitoa_size(unsigned int n)
{
	size_t	size;

	size = 0;
	while (n > 9)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

char			*ft_uitoa(unsigned int n)
{
	char		*str;
	size_t		size;

	size = ft_uitoa_size(n);
	str = malloc(sizeof(str) * size + 1);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[size] = '\0';
	size--;
	while (n)
	{
		str[size] = ((n % 10) + '0');
		size--;
		n = n / 10;
	}
	return (str);
}
