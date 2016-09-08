/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 10:27:15 by rbromilo          #+#    #+#             */
/*   Updated: 2016/09/06 12:06:10 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_split(t_split_string *sp)
{
	size_t	i;

	i = 0;
	while (i < sp->words)
	{
		ft_strdel(&sp->strings[i]);
		++i;
	}
	free(sp->strings);
	sp->strings = NULL;
}
