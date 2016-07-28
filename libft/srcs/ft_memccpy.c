/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 10:55:35 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/25 18:02:49 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	unsigned char	ch;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	ch = (unsigned char)c;
	while (n--)
	{
		if ((*ptr_dest++ = *ptr_src++) == ch)
			return (ptr_dest);
	}
	return (NULL);
}
