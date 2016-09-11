/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_addstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 12:20:18 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 10:40:54 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_echo_addstr(char **str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = 0;
	if (*str != NULL)
		len += ft_strlen(*str);
	new_str = (char *)malloc(sizeof(char) * (len + 2));
	while (j <= len)
	{
		if (j == len)
			new_str[j] = c;
		else if (*str != NULL && (*str)[i] != '\0')
		{
			new_str[j] = (*str)[i];
			i++;
		}
		j++;
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
}
