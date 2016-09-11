/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_esc_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:25:31 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 11:46:47 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	ft_echo_esc_char(char **new_str, int esc_char)
{
	if (esc_char == 'a')
		ft_echo_addstr(new_str, '\a');
	else if (esc_char == 'b')
		ft_echo_addstr(new_str, '\b');
	else if (esc_char == 'c')
		return (-1);
	else if (esc_char == 'e')
		ft_echo_addstr(new_str, 27 + '0');
	else if (esc_char == 'f')
		ft_echo_addstr(new_str, 12 + '0');
	else if (esc_char == 'n')
		ft_echo_addstr(new_str, '\n');
	else if (esc_char == 'r')
		ft_echo_addstr(new_str, '\r');
	else if (esc_char == 't')
		ft_echo_addstr(new_str, '\t');
	else if (esc_char == 'v')
		ft_echo_addstr(new_str, 11 + '0');
	return (0);
}
