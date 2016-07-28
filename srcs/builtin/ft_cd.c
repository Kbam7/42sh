/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 13:29:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 18:53:32 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	change_dir(char *path)
{
	if (chdir(path) != 0)
		return (err(ERR_CHDIR, path));
// Update current working directory and OLDPWD. OLDPWD is a shell variable, not environment var
	
	return (EXIT_SUCCESS);
}

int			ft_cd(char **args, t_shell *s)
{
	char	*last_dir;

// change this to use get_args function. see setenv()

	if (args[1] && args[1][0] != '~')
		if (args[1][0] == '-')
			if ((last_dir = ft_getenv("OLDPWD", s)) == NULL)
				ft_putendl("bash: cd: OLDPWD not set");
			else
				change_dir(last_dir);
		else
			change_dir(args[1]);
	else if (args[1][0] == '~')
		if ((change_dir(ft_getenv("HOME", s))) != 1)
			return (err(ERR_CHDIR, ft_getenv("HOME", s)));
	return (EXIT_SUCCESS);
}
