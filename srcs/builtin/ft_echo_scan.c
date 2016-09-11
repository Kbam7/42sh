/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 11:14:32 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 11:51:41 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	ft_echo_break(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	else if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, "||") == 0)
		return (1);
	else if (ft_strcmp(str, "&") == 0)
		return (1);
	else if (ft_strcmp(str, "&&") == 0)
		return (1);
	else if (ft_strcmp(str, ";") == 0)
		return (1);
	return (0);
}

char		*ft_echo_scan(char **args, t_shell *s)
{
	int		i;
	int		trigger;
	int		flag;
	int		new_line;
	char	*new;

	i = 1;
	trigger = 0;
	flag = 0;
	new_line = 1;
	while (args[i])
	{
		if (ft_echo_break(args[i]) && trigger == 0)
			break ;
		if (flag != -1 && args[i][0] == '-' && trigger == 0)
			ft_echo_isflag(args[i], &flag, &new_line);
		ft_echo_env(&new, args[i], &flag, s);
		ft_echo_string(&new, args[i], &trigger, &flag);
		if (args[i + 1] != '\0' && ft_echo_skip(args[i]) == 0)
			ft_echo_addstr(&new, ' ');
		i++;
	}
	if (new_line == 1)
		ft_echo_addstr(&new, '\n');
	return (new);
}
