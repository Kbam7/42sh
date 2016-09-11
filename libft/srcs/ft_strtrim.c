/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:23:58 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 12:00:53 by tmack            ###   ########.fr       */
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
	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	while (s[start] != '\0' && ft_iswhtspc(s[start]))
		start++;
	while (end > start && s[end] != '\0' && ft_iswhtspc(s[end]))
		end--;
	if (start > end)
		return (NULL);
	if ((new_str = (char *)malloc(sizeof(char) * (end - start + 2))) == NULL)
		return (NULL);
	while (++i <= (end - start))
		new_str[i] = s[start + i];
	new_str[i] = '\0';
	return (new_str);
}
