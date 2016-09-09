/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 14:39:02 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/05 11:28:46 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

/*
char	*ft_cd_get_path(t_shell *s)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 1;
	path = input[1];
	while (input[i])
	{
		if (input[i + 1])
		{
			tmp = path;
			path = ft_strjoin(path, input[i + 1]);
			ft_strdel(&tmp);
		}
		++i;
	}
	return (s->input);
}
*/

int		cd_invalid_input(char *input)
{
	char	*tmp;

	tmp = ft_strjoinstr("cd: Invalid option/path -- '", input, "'");
	err(ERR_INVALID_ARG, tmp);
	ft_strdel(&tmp);
	return (ERR_INVALID_ARG);
}

void	cd_set_arg(char c, t_shell *s)
{
	s->func_opt.cd.l = (c == 'l' ? 1 : s->func_opt.cd.l);
	s->func_opt.cd.l = (c == 'L' ? 1 : s->func_opt.cd.l);
	if (s->func_opt.cd.l)
		s->func_opt.cd.p = 0;
}
