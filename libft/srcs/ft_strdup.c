/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:01:20 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/15 12:24:43 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		len;

	len = ft_strlen(s);
	s2 = (char*)malloc(sizeof(*s) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	ft_strcpy(s2, s);
	return (s2);
}
