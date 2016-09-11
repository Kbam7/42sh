/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_output_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 13:05:08 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 13:09:36 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	open_output_file(int append, t_shell *s)
{
	int	path;
	int	i;

	i = s->redir.rdr_i;
	if (append)
		path = open(s->redir.cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		path = open(s->redir.cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (path < 0)
		err(ERR_CREATE, s->redir.cmd[i + 1]);
	return (path);
}

static int	check_duplicate(char *str, int pos, t_shell *s)
{
	char	*tmp;

	if (str[pos + 1] == '&')
	{
		if (str[pos + 2] == '-')
			close(s->redir.pre_fd);
		else
		{
			tmp = ft_strsub(str, (pos + 2), (ft_strlen(str) - (pos + 2)));
			s->redir.post_fd = ft_atoi(tmp);
			ft_strdel(&tmp);
			dup2(s->redir.post_fd, s->redir.pre_fd);
		}
		return (1);
	}
	else
		return (0);
}

static void	check_redir_position(char *str, int pos, t_shell *s)
{
	int		path;
	char	*tmp;

	if (pos > 0 && ft_isdigit(str[pos - 1]))
	{
		tmp = ft_strsub(str, 0, pos);
		s->redir.pre_fd = ft_atoi(tmp);
		ft_strdel(&tmp);
		if (!check_duplicate(str, pos, s))
			if ((path = open_output_file(s->redir.appnd, s)) > -1)
			{
				dup2(path, s->redir.pre_fd);
				close(path);
			}
	}
	if (pos == 1 && str[pos - 1] == '&')
	{
		if ((path = open_output_file(s->redir.appnd, s)) > -1)
		{
			dup2(path, STDOUT_FILENO);
			dup2(path, STDERR_FILENO);
			close(path);
		}
	}
}

int			child_output_redir(char *str, t_shell *s)
{
	int		pos;
	int		path;

	pos = get_pos(str, '>');
	s->redir.appnd = (str[pos + 1] == '>') ? 1 : 0;
	if (str[pos] == '>')
	{
		s->redir.pre_fd = STDOUT_FILENO;
		if (s->pipe.n_pipes)
			dup2(s->pipe.pipes[s->pipe.pipe_i][0], STDIN_FILENO);
		if (pos == 0)
			if (!check_duplicate(str, pos, s))
				if ((path = open_output_file(s->redir.appnd, s)) > -1)
				{
					dup2(path, STDOUT_FILENO);
					close(path);
				}
		check_redir_position(str, pos, s);
	}
	return (EXIT_SUCCESS);
}
