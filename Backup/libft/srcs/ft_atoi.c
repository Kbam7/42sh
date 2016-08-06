/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:14:56 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/15 11:47:56 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	neg;

	neg = 0;
	res = 0;
	while (*nptr == '\n' || *nptr == '\t' || *nptr == '\r' || *nptr == ' ')
		++nptr;
	if (*nptr == '-')
	{
		++neg;
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - 48);
		++nptr;
	}
	if (neg)
		return (-res);
	return (res);
}
