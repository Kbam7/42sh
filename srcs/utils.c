/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:24:20 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/07 17:23:07 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		ft_sleep(int sec, int nsec)
{
	struct timespec	time;

	time.tv_sec = sec;
	time.tv_nsec = nsec;
	return (nanosleep(&time, NULL));
}

int		check_rights(char *path, int r, int w, int x)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (ft_strlen(path) > MAXPATH)
		return (err(ERR_MAX_PATHLEN, path));
	if (r && access(path, F_OK | R_OK) < 0)
		ret = err(ERR_NO_READ, path);
	if (w && access(path, F_OK | W_OK) < 0)
		ret = err(ERR_NO_WRITE, path);
	if (x && access(path, F_OK | X_OK) < 0)
		ret = err(ERR_NO_EXEC, path);
	return (ret);
}

char	***check_env_type(int type, t_shell *s)
{
	if (type == 1)
		return (&s->env_var);
	else
		return (&s->shell_var);
}

void	print_variables(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_putendl_fd(env[i], STDOUT_FILENO);
		++i;
	}
}
