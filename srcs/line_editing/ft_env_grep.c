/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_grep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 11:09:36 by tmack             #+#    #+#             */
/*   Updated: 2016/08/22 22:19:15 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    ft_home_path(t_shell *s)
{
    char    **dir;
    int     i;

    dir = NULL;
    i = 0;
	s->line->home_path = NULL;
    while (s->line->env[i])
    {
        {
            dir = ft_strsplit(s->line->env[i], '=');
            break ;
        }
        i++;
    }
    if (s->line->home_path != NULL)
        free(s->line->home_path);
    s->line->home_path = ft_strdup(dir[1]);
    ft_free_2(dir);
    free(dir);
}

void    ft_user(t_shell *s)
{
    int     i;
    char    **str;

    str = NULL;
    i = 0;
    while (s->line->env[i])
    {
        if (ft_strncmp(s->line->env[i], "USER=", 4) == 0)
        {
            str = ft_strsplit(s->line->env[i], '=');
            break ;
        }
        i++;
    }
    s->line->user = ft_strdup(str[1]);
    ft_free_2(str);
    free(str);
}

void    ft_oldpwd(t_shell *s)
{
    int     i;
    char    **str;

    str = NULL;
    i = 0;
    while (s->line->env[i])
    {
        if (ft_strncmp(s->line->env[i], "OLDPWD=", 4) == 0)
        {
            str = ft_strsplit(s->line->env[i], '=');
            break ;
        }
        i++;
    }
    if (s->line->oldpwd != NULL)
        free(s->line->oldpwd);
    s->line->oldpwd = ft_strdup(str[1]);
    ft_free_2(str);
    free(str);
}

