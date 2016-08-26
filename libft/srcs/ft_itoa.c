/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 12:50:26 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/15 13:00:15 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_size(int n)
{
	int		size;

	size = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n > 9)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		neg;

	neg = 1;
	size = ft_itoa_size(n);
	str = malloc(sizeof(str) * size + 1);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[size] = '\0';
	if (n < 0)
	{
		neg = -1;
		str[0] = '-';
	}
	size--;
	while (n)
	{
		str[size] = (((n % 10) * neg) + '0');
		size--;
		n = n / 10;
	}
	return (str);
}
