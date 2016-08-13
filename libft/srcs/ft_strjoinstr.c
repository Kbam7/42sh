/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 15:07:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/13 10:29:49 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinstr(char *s1, char *s2, char *s3)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(s1);
	len += ft_strlen(s2);
	len += ft_strlen(s3);
	new_str = ft_strnew(len + 1);
	if (new_str == NULL)
		return (NULL);
	new_str = ft_strcat(new_str, s1);
	new_str = ft_strcat(new_str, s2);
	new_str = ft_strcat(new_str, s3);
	new_str[len] = '\0';
	return (new_str);
/*
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(s1, s2);
	str = ft_strjoin(tmp, s3);
	free(tmp);
	return (str);
*/
}




