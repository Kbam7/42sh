/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:42 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/16 22:35:11 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	set_arg(char c, t_shell *s)
{
	s->func_opt.env.u = (c == 'u' ? 1 : s->func_opt.env.u);
	s->func_opt.env.i = (c == 'i' ? 1 : s->func_opt.env.i);
}

static int	get_args(char **input, t_shell *s)
{
	int		i;
	int		j;
	char	*tmp;
	char	*ch;

	j = 0;
	while (input[++j])
	{
		i = 0;
		while (input[j][i++])
			if (ft_strchr("-ui", input[j][i]))
				set_arg(input[j][i], s);
			else
			{
				ch = ft_ctostr(input[j][i]);
				tmp = ft_strjoinstr("env: Invalid option -- '", ch, "'");
				i = err(ERR_INVALID_ARG, tmp);
				ft_strdel(&ch);
				ft_strdel(&tmp);
				return (i);
			}
	}
	return (EXIT_SUCCESS);
}

int			ft_env(char **input, t_shell *s)
{
	get_args(input, s);
	print_variables(s->env_var, s);
	return (EXIT_SUCCESS);
}
