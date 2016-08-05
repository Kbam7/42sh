/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 15:07:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 00:29:21 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinstr(char *s1, char *s2, char *s3)
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
