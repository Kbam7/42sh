/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 16:59:06 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/03 17:53:59 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_ctrl_l(char *buff, t_shell *s)
{
	if (buff[0] == 12 && buff[1] == 0)
	{
		tputs(tgetstr("cl", 0), 1, ft_putchar_re);
		ft_put_string(s);
	}
}
