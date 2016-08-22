/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 11:09:36 by tmack             #+#    #+#             */
/*   Updated: 2016/08/07 11:59:56 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_echo1(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\\')
		i++;
	if (line[i - 1] == ' ' && line[i] != ' ')
	{
		ft_putchar(' ');
		ft_putchar(line[i]);
	}
	else
		ft_putchar(line[i]);
	return (i);
}

void	ft_echo(char *line)
{
	int		i;
	int		bol;

	i = 5;
	bol = 0;
	while (line[i])
	{
		if (line[i] == '"')
			bol = 1;
		else if (bol == 0)
		{
			if (line[i] == '"')
			{
				bol = 1;
				continue ;
			}
			i = ft_echo1(line, i);
		}
		else if (line[i] == '\\')
			i++;
		else
			ft_putchar(line[i]);
		i++;
	}
	ft_putchar('\n');
}
