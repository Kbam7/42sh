/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:14:04 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/15 11:14:07 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;

	i = 0;
	while (big[i] != '\0' && len--)
	{
		j = i;
		while (little[j - i] == big[j])
		{
			j++;
			if (little[j - i] == '\0')
				return ((char*)big + i);
		}
		i++;
	}
	return (0);
}
