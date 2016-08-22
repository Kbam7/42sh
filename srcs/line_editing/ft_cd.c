/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 07:27:14 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 23:15:24 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_cd1(t_shell *s)
{
	int		i;
	char	**temp1;

	temp1 = NULL;
	i = -1;
	while (s->line->env[++i])
	{
		if (ft_strncmp(s->line->env[i], "PWD=", 3) == 0 &&
                ft_strncmp(s->line->env[i], "OLDPWD=", 6) != 0)
			temp1 = ft_strsplit(s->line->env[i], '=');
    }
    i = -1;
    while (s->line->env[++i])
    {
		if (ft_strncmp(s->line->env[i], "OLDPWD=", 6) == 0)
        {
            if (s->line->oldpwd != NULL)
                free(s->line->oldpwd);
            s->line->oldpwd = ft_strjoin("OLDPWD=", temp1[1]);
            free(s->line->env[i]);
			s->line->env[i] = ft_strdup(s->line->oldpwd);
        }
		if (ft_strncmp(s->line->env[i], "PWD=", 3) == 0)
        {
            if (s->line->pwd != NULL)
                free(s->line->pwd);
            s->line->pwd = ft_strjoin("PWD=", ft_pwd());
            free(s->line->env[i]);
			s->line->env[i] = ft_strdup(s->line->pwd);
        }
    }
	ft_free_2(temp1);
    free(temp1);
}

int     ft_cd(char **args, t_shell *s)
{
	int		i;

    i = ft_nbr_y(args);
	if (i > 2)
	{
		ft_putstr("to many argss");
		return (0);
	}
	if (args[1] == NULL || (ft_strstr(args[1], s->line->user) != NULL &&
				args[1][0] == '~') || ft_strcmp("~", args[1]) == 0 ||
			(args[1][0] == '-' && args[1][1] == '-'))
	    chdir(s->line->home_path);
	else if (args[1][0] == '-')
	{
        ft_oldpwd(s);
		ft_putendl(s->line->oldpwd);
		chdir(s->line->oldpwd);
	}
	else if (chdir(args[1]) == 0)
		;
	else
		ft_putendl("cd error");
	ft_cd1(s);
    return (1);
}
