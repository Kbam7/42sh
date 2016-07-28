/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 16:51:31 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 01:34:50 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	get_arg(int ac, char **argv, t_shell *s)
{
	int		i;
	char	*tmp;

	s->argv = ft_tabdup(argv, ac);
	s->arg_p = 0;
	s->arg_u = 0;
	while (ac-- != 1)
	{
		if (argv[ac][0] == '-' && argv[ac][1])
		{
			i = 0;
			while (argv[ac][++i])
			{
				s->arg_p = (argv[ac][i] == 'p') ? 1 : s->arg_p;
				s->arg_u = (argv[ac][i] == 'u') ? 1 : s->arg_u;
			}
		}
		else
		{	
			tmp = ft_nstrjoin(argv[0], ": ", argv[ac]);
			err(ERR_INVALID_ARG, tmp);
			ft_strdel(&tmp);
		}
	}
}
