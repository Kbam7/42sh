/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 13:43:50 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 22:19:15 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	**ft_semi(t_shell *s)
{
	char	**semi;
	int		i;
    char    *temp;

	semi = NULL;
	i = 0;
	if ((semi = ft_strsplit(s->line->new_line, ';')) == NULL)
	{
		s->line->c_semi = 0;
		return (NULL);
	}
	else
	{
		while (semi[i])
        {
            temp = ft_strdup(semi[i]);
            free (semi[i]);
			semi[i] = ft_strtrim(temp);
            free(temp);
            i++;
        }
        semi[i] = NULL;
		s->line->nbr_semi = i;
		return (semi);
	}
}
