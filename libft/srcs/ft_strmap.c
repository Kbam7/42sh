/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:22:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/05/15 13:41:50 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			new_str[i] = f(s[i]);
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (NULL);
}
