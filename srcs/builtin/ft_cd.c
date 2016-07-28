/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:29:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 21:51:56 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	set_arg(char c, t_shell *s)
{
	s->func_opt.cd.l = (c == 'l' ? 1 : s->func_opt.cd.l);
	s->func_opt.cd.l = (c == 'L' ? 1 : s->func_opt.cd.l);
	if (s->func_opt.cd.l)
		s->func_opt.cd.p = 0;
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
			if (ft_strchr("-lL", input[j][i]))
				set_arg(input[j][i], s);
			else
			{
				ch = ft_ctostr(input[j][i]);
				tmp = ft_nstrjoin("env: Invalid option -- '", ch,"'");
				i = err(ERR_INVALID_ARG, tmp);
				ft_strdel(&ch);
				ft_strdel(&tmp);
				return (i);
			}
	}
	return (EXIT_SUCCESS);
}

static int	change_dir(char *path, t_shell *s)
{
	if (chdir(path) != 0)
		return (err(ERR_CHDIR, path));
// Update current working directory and OLDPWD. OLDPWD is a shell variable, not environment var
	ft_set(2, "OLDPWD", ft_getenv("PWD", s), s);
	ft_set(1, "PWD", path, s);
	return (EXIT_SUCCESS);
}

int			ft_cd(char **input, t_shell *s)
{
	char	*last_dir;

	get_args(input, s);
//	if (s->func_opt.cd.l)
//		follow links
//	else	// default -- opt 'p'
//		dont follow links
	if (input[1] && input[1][0] != '~')
		if (input[1][0] == '-')
			if ((last_dir = ft_getenv("OLDPWD", s)) == NULL)
				err("cd: OLDPWD not set");
			else
				change_dir(last_dir);
		else
			change_dir(input[1]);
	else if (input[1][0] == '~')
		if ((change_dir(ft_getenv("HOME", s))) != EXIT_SUCCESS)
			return (err(ERR_CHDIR, ft_getenv("HOME", s)));
	return (EXIT_SUCCESS);
}
