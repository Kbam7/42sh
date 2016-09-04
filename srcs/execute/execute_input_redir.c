/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_input_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 13:05:19 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/01 14:31:00 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	open_input_file(t_shell *s)
{
	int	path;
	int	i;

	i = s->redir.rdr_i;
		path = open(s->redir.cmd[i + 1], O_RDONLY, 0664); // S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
	if (path < 0)
		err(ERR_NO_READ, s->redir.cmd[i + 1]);
	return (path);
}

static int	check_duplicate(char *str, int pos, t_shell *s)
{
	char	*tmp;

	if (str[pos + 1] == '&')	// ('<&')
	{
//dprintf(2, "child_input_redir() -- check_duplicate() -- s->redir.pre_fd = '%d'\n", s->redir.pre_fd); // debug
		if (str[pos + 2] == '-')	// ('>&-' || '<&-')
		{
//dprintf(2, "child_input_redir() -- check_duplicate() -- Found '%d>&-' CLOSING s->redir.pre_fd = '%d'\n", s->redir.pre_fd, s->redir.pre_fd); // debug
			close(s->redir.pre_fd);
		}
		else
		{ // duplicate fd defined after '&', ('<&fd') -- and overwrite it with the pre_fd
//dprintf(2, "child_input_redir() -- check_duplicate() -- DUPLICATING INPUT FD -- s->redir.pre_fd = '%d'\n", s->redir.pre_fd); // debug
			tmp = ft_strsub(str, (pos + 2), (ft_strlen(str) - (pos + 2)));
			s->redir.post_fd = ft_atoi(tmp);
		//	check if s->redir.post_fd is open for reading
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

int		child_input_redir(char *str, t_shell *s)
{
	int		pos;
	int		path;
	char	*tmp;

//dprintf(2, "child_input_redir() -- \n");
	pos = get_pos(str, '<');
	if (str[pos] == '<')
	{
		s->redir.pre_fd = STDIN_FILENO; 

//		if (s->pipe.n_pipes)
//			dup2(s->pipe.pipes[s->pipe.pipe_i][0], STDIN_FILENO);

		if (str[pos] == str[pos + 1])				// '<<'
			ft_heredocs(str, pos, s);	
		else
		{
			if (pos > 0 && ft_isdigit(str[pos - 1])) 	// ('2<' || '43<')
			{
				tmp = ft_strsub(str, 0, pos);
				s->redir.pre_fd = ft_atoi(tmp);
				ft_strdel(&tmp);
//dprintf(2, "child_input_redir() -- '5>' -- \n");
/*			if (!check_duplicate(str, pos, s))
				if ((path = open_input_file(s)) > -1)
				{
					dup2(path, s->redir.pre_fd);
					close(path);
				}
*/			}
			if (!check_duplicate(str, pos, s))
				if ((path = open_input_file(s)) > -1)
				{
					dup2(path, s->redir.pre_fd);
					close(path);
				}
		}
	}
	return (EXIT_SUCCESS);
}
