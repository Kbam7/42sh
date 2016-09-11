/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:42 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 11:48:57 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	set_arg(char c, t_shell *s)
{
	s->func_opt.env.u = (c == 'u' ? 2 : 3);
	s->func_opt.env.i = (c == 'i' ? 2 : 3);
}

static int	get_args(char **input, t_shell *s)
{
	int		i;
	int		j;
	char	*tmp;
	char	*ch;

	j = 0;
	i = 0;
	if (input[1])
	{
		if (input[1][0] == '-')
			set_arg(input[1][1], s);
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
	if (s->func_opt.env.i == 2)
	{
		free_tab((void ***)&s->env_var, ft_tablen(s->env_var));
		free(s->env_var);
		s->env_var = NULL;
	}
	else if (s->func_opt.env.u == 2)
		ft_unsetenv(input[2], s);
	print_variables(s->env_var);
	return (EXIT_SUCCESS);
}
