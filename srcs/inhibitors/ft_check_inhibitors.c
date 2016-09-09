/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_inhibitors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 07:18:42 by kgani             #+#    #+#             */
/*   Updated: 2016/09/09 10:45:55 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int ft_check_operators(char c)
{
	int i;
	char *ops;
		
	i = 0;
	ops = ft_strdup(";|&<>");
	while(ops[i])
	{
		if (c == ops[i])
		{
			ft_strdel(&ops);
			return(1);
		}
		i++;
	}
	if (ops)
		ft_strdel(&ops);
	return (0);
}

int ft_check_inhibitors(char *str)
{
	int		trigger;
	int		found;

	trigger = 0;
	found = 0;
	while(*str)
	{
		if  ((*str == 34 || *str == 39) && *str == trigger && trigger != 0)
			trigger = 0;
		if ((*str == 39 || *str == 34) && trigger == 0)
			trigger = *str;
		if ((trigger == 34 || trigger == 39) && ft_check_operators(*str) == 0)
			found = 1;
		str++;
	}
	return (found);
}
