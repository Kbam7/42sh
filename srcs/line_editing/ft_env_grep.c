#include "shell.h"

void    ft_home_path(t_shell *shell)
{
    char    **dir;
    int     i;

    dir = NULL;
    i = 0;
	shell->home_path = NULL;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], "HOME=", 4) == 0)
        {
            dir = ft_strsplit(shell->env[i], '=');
            break ;
        }
        i++;
    }
    if (shell->home_path != NULL)
        free(shell->home_path);
    shell->home_path = ft_strdup(dir[1]);
    ft_free_2(dir);
    free(dir);
}

void    ft_user(t_shell *shell)
{
    int     i;
    char    **str;

    str = NULL;
    i = 0;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], "USER=", 4) == 0)
        {
            str = ft_strsplit(shell->env[i], '=');
            break ;
        }
        i++;
    }
    shell->user = ft_strdup(str[1]);
    ft_free_2(str);
    free(str);
}

void    ft_oldpwd(t_shell *shell)
{
    int     i;
    char    **str;

    str = NULL;
    i = 0;
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], "OLDPWD=", 4) == 0)
        {
            str = ft_strsplit(shell->env[i], '=');
            break ;
        }
        i++;
    }
    if (shell->oldpwd != NULL)
        free(shell->oldpwd);
    shell->oldpwd = ft_strdup(str[1]);
    ft_free_2(str);
    free(str);
}

