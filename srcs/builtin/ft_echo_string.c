/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:17:09 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 06:13:02 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_echo_string_trigger(char **new_str, char c, int *trigger)
{
		if ((c == 34 || c == 39) && *trigger == 0)
			*trigger = c;
		else if ((c == 34 || c == 39) && c == *trigger)
			*trigger = 0;
		if ((c == 34 || c == 39) && *trigger != 0 && c != *trigger)
			ft_echo_addstr(new_str, c);
		if (c != 34 && c != 39 && c != '\\' && *trigger)
			ft_echo_addstr(new_str, c);
		else if (c != 34 && c != 39 && c != '\\')
			ft_echo_addstr(new_str, c);
}

void		ft_echo_string(char **new_str, char *arg, int *trigger, int *flag)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	if (ft_echo_skip(arg) && *trigger != 39 && *trigger != 34)
		return ;
	if (*flag == 0)
		*flag = -1;
	while (arg[i] != '\0')
	{
		if ((ret = ft_echo_esc(new_str, arg, i, *trigger)) != -1)
			i += ret;
		else
			break;
		if (arg[i - 2] != '\\' && (arg[i - 1] != '\\'))
			ft_echo_string_trigger(new_str, arg[i], trigger);
		i++;
	}
}
