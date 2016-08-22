/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 07:27:14 by tmack             #+#    #+#             */
/*   Updated: 2016/08/18 17:12:54 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_cd1(t_shell *shell)
{
	int		i;
	char	**temp1;

	temp1 = NULL;
	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 3) == 0 &&
                ft_strncmp(shell->env[i], "OLDPWD=", 6) != 0)
			temp1 = ft_strsplit(shell->env[i], '=');
    }
    i = -1;
    while (shell->env[++i])
    {
		if (ft_strncmp(shell->env[i], "OLDPWD=", 6) == 0)
        {
            if (shell->oldpwd != NULL)
                free(shell->oldpwd);
            shell->oldpwd = ft_strjoin("OLDPWD=", temp1[1]);
            free(shell->env[i]);
			shell->env[i] = ft_strdup(shell->oldpwd);
        }
		if (ft_strncmp(shell->env[i], "PWD=", 3) == 0)
        {
            if (shell->pwd != NULL)
                free(shell->pwd);
            shell->pwd = ft_strjoin("PWD=", ft_pwd());
            free(shell->env[i]);
			shell->env[i] = ft_strdup(shell->pwd);
        }
    }
	ft_free_2(temp1);
    free(temp1);
}

int     ft_cd(char **args, t_shell *shell)
{
	int		i;

    i = ft_nbr_y(args);
	if (i > 2)
	{
		ft_putstr("to many argss");
		return (0);
	}
	if (args[1] == NULL || (ft_strstr(args[1], shell->user) != NULL &&
				args[1][0] == '~') || ft_strcmp("~", args[1]) == 0 ||
			(args[1][0] == '-' && args[1][1] == '-'))
	    chdir(shell->home_path);
	else if (args[1][0] == '-')
	{
        ft_oldpwd(shell);
		ft_putendl(shell->oldpwd);
		chdir(shell->oldpwd);
	}
	else if (chdir(args[1]) == 0)
		;
	else
		ft_putendl("cd error");
	ft_cd1(shell);
    return (1);
}
