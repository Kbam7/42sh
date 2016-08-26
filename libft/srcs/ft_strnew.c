/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 11:20:41 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/25 17:57:00 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new_str;

	new_str = (char *)malloc(size + 1);
	if (new_str == NULL)
		return (NULL);
	ft_memset(new_str, 0, size + 1);
	return (new_str);
}
