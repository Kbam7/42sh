/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_input_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 13:05:19 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 13:18:50 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	open_input_file(t_shell *s)
{
	int	path;
	int	i;

	i = s->redir.rdr_i;
	path = open(s->redir.cmd[i + 1], O_RDONLY, 0664);
	if (path < 0)
		err(ERR_NO_READ, s->redir.cmd[i + 1]);
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
			if (fcntl(s->redir.post_fd, F_GETFL) < 0)
				return (err(ERR_BADFD, tmp));
			ft_strdel(&tmp);
			dup2(s->redir.post_fd, s->redir.pre_fd);
		}
		return (1);
	}
	else
		return (0);
}

static void	input_redir_file(t_shell *s)
{
	int		path;

	if ((path = open_input_file(s)) > -1)
	{
		dup2(path, s->redir.pre_fd);
		close(path);
	}
}

int			child_input_redir(char *str, t_shell *s)
{
	int		pos;
	char	*tmp;

	pos = get_pos(str, '<');
	if (str[pos] == '<')
	{
		s->redir.pre_fd = STDIN_FILENO;
		if (str[pos] == str[pos + 1])
			ft_heredocs(s);
		else
		{
			if (pos > 0 && ft_isdigit(str[pos - 1]))
			{
				tmp = ft_strsub(str, 0, pos);
				s->redir.pre_fd = ft_atoi(tmp);
				ft_strdel(&tmp);
			}
			if (!check_duplicate(str, pos, s))
				input_redir_file(s);
		}
	}
	return (EXIT_SUCCESS);
}
