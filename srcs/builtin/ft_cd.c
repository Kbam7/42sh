/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:29:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/05 12:24:34 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	change_dir(char *path, t_shell *s)
{
	char	*cwd;

	if ((cwd = (char *)malloc(sizeof(char) * 4096)) == NULL)
		err(ERR_MALLOC, "ft_cd() - change_dir()\n");
	if (access(path, F_OK) != 0)
	{
		ft_strdel(&cwd);
		return (err(ERR_NO_FILE, path));
	}
	if ((check_rights(path, 'r', 0, 'x') != EXIT_SUCCESS) || chdir(path) != 0)
	{
		ft_strdel(&cwd);
		return (err(ERR_CHDIR, path));
	}
	ft_set(1, "OLDPWD", ft_getenv("PWD", s), s);
	ft_set(1, "PWD", getcwd(cwd, 4096), s);
	s->cwd = ft_getenv("PWD", s);
	ft_strdel(&cwd);
	return (EXIT_SUCCESS);
}

int			cd_change_to_fullpath(char *input, t_shell *s)
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

int			change_to_home_dir(t_shell *s)
{
	char	*tmp;

	if ((tmp = ft_getenv("HOME", s)) == NULL)
		err(ERR_CHDIR, "cd: 'HOME' variable not set.");
	else
		return (change_dir(tmp, s));
	return (EXIT_FAILURE);
}

int			change_to_oldpwd(t_shell *s)
{
	char	*tmp;

	if ((tmp = ft_getenv("OLDPWD", s)) == NULL)
		err(ERR_CHDIR, "cd: 'OLDPWD' variable not set.");
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
		if (ft_strcmp(tmp, "-") == 0)
			return (change_to_oldpwd(s));
		else if (ft_strcmp(tmp, "--") == 0 || ft_strcmp(tmp, "~") == 0)
			return (change_to_home_dir(s));
		else if (tmp[0] == '~' && ft_isprint(tmp[1]))
			return (cd_change_to_fullpath(tmp, s));
		else if (tmp[0] == '-' && ft_strchr("pPlL", tmp[1]) != 0)
			cd_set_arg(tmp[1], s);
		else if (change_dir(tmp, s) != EXIT_SUCCESS)
			return (cd_invalid_input(tmp));
	}
	if (ft_strcmp(input[0], "cd") == 0 && input[1] == NULL)
		return (change_to_home_dir(s));
	return (EXIT_SUCCESS);
}
