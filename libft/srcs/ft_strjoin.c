/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:23:47 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/09 20:42:52 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(s1);
	len += ft_strlen(s2);
	new_str = ft_strnew(len + 1);
	if (new_str == NULL)
		return (NULL);
	new_str = ft_strcat(new_str, s1);
	new_str = ft_strcat(new_str, s2);
	new_str[len] = '\0';
	return (new_str);
}
