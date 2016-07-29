/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:29:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/29 03:31:57 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	change_dir(char *path, t_shell *s)
{
// check if path exists, then check rights if it exists. --  access(path, F_OK) . .. .
	if ((check_rights(path, 'r', 0, 'x') != EXIT_SUCCESS) || chdir(path) != 0)
		return (err(ERR_CHDIR, path));
// Update current working directory and OLDPWD. OLDPWD is a shell variable, not environment var
	ft_set(2, "OLDPWD", ft_getenv("PWD", s), s);
	ft_set(1, "PWD", path, s);
	return (EXIT_SUCCESS);
}

static void	set_arg(char c, t_shell *s)
{
	s->func_opt.cd.l = (c == 'l' ? 1 : s->func_opt.cd.l);
	s->func_opt.cd.l = (c == 'L' ? 1 : s->func_opt.cd.l);
	if (s->func_opt.cd.l)
		s->func_opt.cd.p = 0;
}

int	cd_invalid_input(char *input)
{
	char	*tmp;

	tmp = ft_nstrjoin("cd: Invalid option/path -- '", input,"'");
	err(ERR_INVALID_ARG, tmp);
	ft_strdel(&tmp);
	return (ERR_INVALID_ARG);
}

int	cd_change_to_fullpath(char *input, t_shell *s)
{
	char	*tmp;
	char	*path;
	int		ret;

	path = ft_getenv("HOME", s);
	tmp = ft_strsub(input, 1, ft_strlen(input) - 1);
	path = ft_strjoin(path, tmp);
	ret = change_dir(path, s);
	ft_strdel(&tmp);
	ft_strdel(&path);
	return (ret);
}

int	change_to_home_dir(t_shell *s)
{
	char	*tmp;

	if ((tmp = ft_getenv("HOME", s)) == NULL)
		ft_putstr("cd: HOME variable not set.");
	else
		return (change_dir(tmp, s));
	return (EXIT_FAILURE);
}

int	change_to_oldpwd(t_shell *s)
{
	char	*tmp;

	if ((tmp = ft_getenv("OLDPWD", s)) == NULL)
		ft_putstr("cd: OLDPWD variable not set.\n");
	else
		return (change_dir(tmp, s));
	return (EXIT_FAILURE);
}

int			ft_cd(char **input, t_shell *s)
{
	int		j;
	char	*tmp;

	j = 0;
	while (input[++j] && j < 2)
	{
		tmp = input[j];

ft_printf("--------- HERE --1 ----------\n");

		if (ft_strcmp(tmp, "-") == 0)
		{
ft_printf("--------- HERE -- 2 ----------\n");

			return (change_to_oldpwd(s));
		}
		else if (ft_strcmp(tmp, "--")  == 0 || ft_strcmp(tmp, "~") == 0)
		{
ft_printf("--------- HERE -- 3 ----------\n");

				 return (change_to_home_dir(s));
		}
		else if (tmp[0] == '~' && ft_isprint(tmp[1]))
		{
ft_printf("--------- HERE -- 4 ----------\n");
			return (cd_change_to_fullpath(tmp, s));
		}
		else if (tmp[0] == '-' && ft_strchr("pPlL", tmp[1]) != 0)
		{
ft_printf("--------- HERE -- 5 ---------- >%s\n", ft_strchr("pPlL", tmp[1]));

			set_arg(tmp[1], s);
		}
		else if (change_dir(tmp, s) != EXIT_SUCCESS)
			return (cd_invalid_input(tmp));
	}
	if (ft_strcmp(input[0], "cd") == 0 && input[1] == NULL)
		return (change_to_home_dir(s));
	return (EXIT_SUCCESS);
}
