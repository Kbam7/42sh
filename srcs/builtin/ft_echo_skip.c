/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_skip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:26:08 by kgani             #+#    #+#             */
/*   Updated: 2016/09/03 18:09:05 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	ft_echo_skip(char *str)
{
<<<<<<< HEAD
	int             new_line;
	int             flag;

	if (ft_echo_isflag(str, &flag, &new_line))
		return (1);
=======
//	int             i;
//	int             found;
//	char    *esc_char;
	int             new_line;
	int             flag;

//	i = 0;
//	found = 0;
	if (ft_echo_isflag(str, &flag, &new_line))
		return (1);
//	esc_char = ft_strdup("abcefnrtv");
>>>>>>> 32a06269e09abf1bfb625371ae57137a226f94da
	if (str[0] && str[0] == '$')
		return (1);
	return (0);

}
