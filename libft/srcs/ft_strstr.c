/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:13:39 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/29 19:57:03 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[i] != '\0')
	{
		j = i;
		while (needle[j - i] == haystack[j])
		{
			j++;
			if (needle[j - i] == '\0')
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
