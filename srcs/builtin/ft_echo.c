/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:12:50 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 06:19:52 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	ft_echo(char **args, t_shell *s)
{
	char	*new;

	new = NULL;
	if (ft_countarray(args) > 1)
	{
		puts((ft_itoa(ft_countarray(args))));
		new = ft_echo_scan(args, s);
		if (new)
			ft_putstr(new);
	}
	else
		ft_putchar('\n');
	ft_echo_clean(new);
	return (EXIT_SUCCESS);
}
