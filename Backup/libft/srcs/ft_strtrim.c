/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:23:58 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/26 23:57:21 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new_str;
	size_t	i;
	size_t	start;
	size_t	end;

	i = -1;
	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] == '\n' || s[start] == ' ' || s[start] == '\t')
		start++;
	while (s[end] == '\n' || s[end] == ' ' || s[end] == '\t')
		end--;
	new_str = (char *)malloc(sizeof(*new_str) * (end - start + 2));
	if (new_str == NULL || s == NULL)
		return (NULL);
	while (++i <= (end - start))
		new_str[i] = s[start + i];
	new_str[i] = '\0';
	return (new_str);
}
