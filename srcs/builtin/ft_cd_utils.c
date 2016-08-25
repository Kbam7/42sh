/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 14:39:02 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/08 16:33:17 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

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
