/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_isflag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:36:27 by kgani             #+#    #+#             */
/*   Updated: 2016/08/31 11:36:49 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int     ft_echo_isflag(char *arg, int *flag, int *new_line)
{
	if (arg[0] && arg[0] == '-')
	{
		if (arg[1] && arg[1] == 'e')
		{
			*flag = 'e';
			return (1);
		}
		else if (arg[1] && arg[1] == 'n')
		{
			*flag = 'n';
			*new_line = -1;
			return (1);
		}
	}
	return (0);
}
