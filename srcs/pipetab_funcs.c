/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipetab_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 17:25:06 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/26 07:29:54 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		**ft_pipedup(int **pipe, int len)
{
	int		i;
	int		**tmp;

	i = -1;
	if ((tmp = (int **)ft_memalloc(sizeof(int *) * (len + 1))) != NULL)
	{
		while (++i < len && pipe[i])
			tmp[i] = (int *)ft_memcpy(tmp[i], pipe[i], 2);
//		while (++i < len)
//			tmp[i] = "\0";
//		tmp[len] = NULL; // ft_memalloc() sets new mem to zero (i.e. NULL)
	}
	return (tmp);
}

int		ft_pipelen(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i] != NULL)
		++i;
	return (i);
}

void	free_pipes(int ***pipes, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_memdel((void **)&(*pipes)[i]);
		++i;
	}
	free(*pipes);
	*pipes = NULL;
}
