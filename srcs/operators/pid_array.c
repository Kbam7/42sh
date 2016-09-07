/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 21:40:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/07 21:56:08 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	delete_var(char ***var, int i)
{
	char			**tmp;

	ft_strdel(&(*var)[i]);
	while ((*var)[i + 1] != NULL)
	{
		++i;
		(*var)[i - 1] = ft_strdup((*var)[i]);
		ft_strdel(&(*var)[i]);
	}
	tmp = ft_tabdup(*var, ft_tablen(*var));
	free_tab((void ***)var, ft_tablen(*var));
	*var = tmp;
}

int			remove_child_pid(pid_t pid, t_shell *s)
{
	char	*pid_str;
	int		len;
	int		i;

	len = ft_tablen(s->pipe.child_pid);
	if (len == 1)
		free_tab((void ***)&s->pipe.child_pid, len);
	else
	{
		pid_str = ft_itoa((int)pid);
		i = 0;
		while (s->pipe.child_pid[i] != NULL)
		{
			if (ft_strcmp(pid_str, s->pipe.child_pid[i]) == 0)
				delete_var(&s->pipe.child_pid, i);
			else
				++i;
		}
		free(pid_str);
	}
	return (len - 1);
}

int			add_child_pid(pid_t pid, t_shell *s)
{
	char	**tmp;
	char	*pid_str;
	int		len;

	pid_str = ft_itoa((int)pid);
	if (s->pipe.child_pid == NULL)
	{
		if ((s->pipe.child_pid = ft_tabnew(pid_str, 1)) == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		len = ft_tablen(s->pipe.child_pid);
		if ((tmp = ft_tabdup(s->pipe.child_pid, len + 1)) == NULL)
			return (EXIT_FAILURE);
		free_tab((void ***)&s->pipe.child_pid, len);
		tmp[len] = ft_strdup(pid_str);
		s->pipe.child_pid = tmp;
	}
	free(pid_str);
	return (EXIT_SUCCESS);
}

int			get_child_pid_index(pid_t pid, t_shell *s)
{
	int		c;
	char	*str;

	c = 0;
	str = ft_itoa((int)pid);
	while (s->pipe.child_pid[c] && ft_strcmp(str, s->pipe.child_pid[c]) != 0)
		++c;
	return (c);	
}
