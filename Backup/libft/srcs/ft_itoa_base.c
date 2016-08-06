/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 12:50:26 by kbamping          #+#    #+#             */
/*   Updated: 2016/06/16 07:27:28 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_n(int *nmbr, unsigned int base, int *store_nmbr)
{
	int	i;

	i = 0;
	while (*nmbr != 0)
	{
		store_nmbr[i] = *nmbr % base;
		*nmbr = *nmbr / base;
		++i;
	}
	return (i);
}

char		*ft_itoa_base(int n, unsigned int base)
{
	static char	base_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
									'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int			cnvtd_nmbr[32];
	int			i;
	int			j;
	char		*res;

	j = 0;
	if (n < 0)
	{
		n = n * -1;
		++j;
	}
	if (n == 0 || base < 2 || base > 16)
		return ("0");
	i = convert_n(&n, base, cnvtd_nmbr);
	res = ft_strnew(i);
	if (j)
		res[0] = '-';
	while (--i >= 0)
		res[j++] = base_digits[cnvtd_nmbr[i]];
	return (res);
}
