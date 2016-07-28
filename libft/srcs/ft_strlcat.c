/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:12:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/25 17:38:24 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*ptr_dst;
	const char	*ptr_src;
	size_t		n;
	size_t		dst_len;

	ptr_dst = dst;
	ptr_src = src;
	n = size;
	while (n-- != 0 && *ptr_dst != '\0')
		ptr_dst++;
	dst_len = ptr_dst - dst;
	n = size - dst_len;
	if (n == 0)
		return (dst_len + ft_strlen(ptr_src));
	while (*ptr_src != '\0')
	{
		if (n != 1)
		{
			*ptr_dst++ = *ptr_src;
			n--;
		}
		ptr_src++;
	}
	*ptr_dst = '\0';
	return (dst_len + (ptr_src - src));
}
