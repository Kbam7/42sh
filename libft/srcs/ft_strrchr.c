/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:13:26 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/17 16:36:22 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	char			*ptr;

	ptr = (char *)s;
	len = ft_strlen(ptr);
	while (ptr[len] != c && len != -1)
		len--;
	if (ptr[len] == c)
		return (&ptr[len]);
	return (NULL);
}
