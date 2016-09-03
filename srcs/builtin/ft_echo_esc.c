/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_esc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:24:39 by kgani             #+#    #+#             */
/*   Updated: 2016/09/01 09:28:32 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	ft_echo_esc(char **new_str, char *arg, int pos, int trigger)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (arg[pos + i] != '\0' && arg[pos + i] == '\\')
	{
		if (arg[pos + i + 1] != '\0')
		{
/*
			if (arg[pos + i + 2] != '\0' && arg[pos + i + 2] == '\\')
			{
				if((ret = ft_echo_esc_char(new_str, arg[pos + i + 2])) != -1)
					ret = 3;
				else
					break;
			}
*/
				if ((ret = ft_echo_esc_char(new_str, arg[pos + i + 1])) != - 1 && \
					trigger != 0 && trigger != -1)
					ret = 2;
				else
					break;
		}
		i++;
	}
	return (ret);
}
