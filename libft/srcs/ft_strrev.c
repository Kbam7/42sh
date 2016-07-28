/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 13:09:49 by kbamping          #+#    #+#             */
/*   Updated: 2016/02/05 13:18:04 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	temp;
	int		c;
	int		l;

	c = 0;
	l = 0;
	l = ft_strlen(str);
	while (--l > c)
	{
		temp = str[c];
		str[c] = str[l];
		str[l] = temp;
		c++;
	}
	return (str);
}
