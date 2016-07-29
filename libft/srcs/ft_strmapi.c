/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:22:30 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/15 13:42:18 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	size_t	len;
	size_t	i;

	if (s && f)
	{
		i = 0;
		len = ft_strlen(s);
		new_str = (char *)malloc(sizeof(*new_str) * len);
		if (new_str == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			new_str[i] = f(i, s[i]);
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (NULL);
}
