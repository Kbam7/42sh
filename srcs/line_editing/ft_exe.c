/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/04 15:42:07 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 12:59:20 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_exit(t_shell *shell)
{
    tputs(tgetstr("vi", 0), 1, ft_putchar_re);
    tputs(tgetstr("ve", 0), 1, ft_putchar_re);
    tputs(tgetstr("te", 0), 1, ft_putchar_re);
    tputs(tgetstr("rs", 0), 1, ft_putchar_re);
	exit(1);
}

char	*ft_pwd(void)
{
	static char		cwd[1024];
	char			temp;
	int				i;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		;
	else
		ft_putstr("pwd error");
	return (cwd);
}
