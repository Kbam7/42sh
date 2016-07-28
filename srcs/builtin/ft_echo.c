/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:29 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 01:39:17 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void		echo_env(char *arg, t_shell *s)
{
	char	*str;

	str = ft_getenv(arg, s);
	if (str != NULL)
		ft_putstr(str);
}

static void		func_print(char **args, t_shell *s)
{
	int	i;
	int	k;

	i = 1;
	while (args[i] != NULL)
	{
		k = 0;
		if (ft_strcmp(args[i], "-n") == 0)
			i++;
		if (args[i][0] == '$')
			echo_env(&(args[i][1]), s);
		while (args[i][k] != '\0' && args[i][0] != '$')
		{
			if (args[i] == args[0])
				i++;
			write(1, &args[i][k], 1);
			k++;
		}
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int				ft_echo(char **args, t_shell *s)
{
	if (!args[1])
		write(1, "\n", 1);
	else
	{
		if (args[1] && !(args[2]))
		{
			if (ft_strcmp(args[1], "-n") == 0)
				return (EXIT_SUCCESS);
			else if (args[1][0] == '$')
				echo_env(&args[1][1], s);
			else
				ft_putstr(args[1]);
		}
		else
			func_print(args, s);
		if (ft_strcmp(args[1], "-n") != 0)
			write(1, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
