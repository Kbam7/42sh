/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 15:07:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/09 15:08:06 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_nstrjoin(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*str;

	if (s1 && s2 && s3)
	{
		tmp = ft_strjoin(s1, s2);
		str = ft_strjoin(tmp, s3);
		free(tmp);
		return (str);
	}
	else
		return (NULL);
}
