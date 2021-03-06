/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 09:59:03 by kgani             #+#    #+#             */
/*   Updated: 2016/09/11 15:57:41 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	ft_check_or(char *str)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && trigger == 0)
		{
			trigger = str[i];
			i++;
		}
		if (str[i] == trigger && trigger != 0)
			trigger = 0;
		if (str[i] == '|' && str[i + 1] == '|' && trigger == 0)
			return (1);
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

static int	ft_check_and(char *str)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && trigger == 0)
		{
			trigger = str[i];
			i++;
		}
		if (str[i] == trigger && trigger != 0)
			trigger = 0;
		if (str[i] == '&' && str[i + 1] == '&' && trigger == 0)
			return (1);
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

static int	ft_check_pipes(char *str)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && trigger == 0)
		{
			trigger = str[i];
			i++;
		}
		if (str[i] == trigger && trigger != 0)
			trigger = 0;
		if (str[i] == '|' && str[i + 1] != '|' && str[i - 1] != '|' &&
				trigger == 0)
			return (1);
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

static int	ft_check_redir(char *str)
{
	int i;
	int trigger;

	i = 0;
	trigger = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && trigger == 0)
		{
			trigger = str[i];
			i++;
		}
		if (str[i] == trigger && trigger != 0)
			trigger = 0;
		if ((str[i] == '>' || str[i] == '<') && trigger == 0)
			return (1);
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

int			process_input(char *cmd, t_shell *s)
{
	int	error;

	error = EXIT_FAILURE;
	if (ft_check_or(cmd))
		return (process_logical_or(cmd, s));
	else if (ft_check_and(cmd))
		return (process_logical_and(cmd, s));
	else if (ft_check_pipes(cmd))
		return (process_pipes(cmd, s));
	else if (ft_check_redir(cmd))
		return (process_redir(cmd, s));
	else
	{
		if (s->input != NULL)
			free_tab((void ***)&s->input, ft_tablen(s->input));
		get_input(cmd, s);
		error = execute_cmd(s);
	}
	return (error);
}
