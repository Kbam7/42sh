/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 13:03:29 by kgani             #+#    #+#             */
/*   Updated: 2016/09/06 09:03:25 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_check_wait_found(int *found, int trigger, char *str)
{
	if (trigger == 92 && *found > 0)
		(*found)--;
	if (*str == 92 && !*str + 1)
	{
		trigger = *str;
		(*found)++;
	}
}

void		ft_check_wait(t_shell *s)
{
	int		found;
	int		trigger;
	char	*str;

	trigger = 0;
	str = s->new_line;
	found = 0;
	while (*str)
	{
		ft_check_wait_found(&found, trigger, str);
		if (*str == 39 || *str == 34)
		{
			trigger = *str;
			found++;
			while (*str && *str != '\0' && str++)
				if (*str == trigger)
				{
					found--;
					break ;
				}
		}
		str++;
	}
	if (found != 0)
		ft_wait(trigger, s);
}
