/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 12:01:21 by tmack             #+#    #+#             */
/*   Updated: 2016/09/11 12:02:04 by tmack            ###   ########.fr       */
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
}
