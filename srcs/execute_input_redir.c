/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_input_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 13:05:19 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/20 13:15:31 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	open_input_file(int append, t_shell *s)
{
	int	path;
	int	i;

	i = s->redir.rdr_i;
	if (append)
		path = open(s->redir.cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0664); // S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
	else
		path = open(s->redir.cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664); // S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
	if (path < 0)
		err(ERR_CREATE, s->redir.cmd[i + 1]);
	return (path);
}

static int	check_duplicate(char *str, int pos, t_shell *s)
{
	char	*tmp;

	if (str[pos + 1] == '&')	// ('>&')
	{

dprintf(2, "child_output_redir() -- check_duplicate() -- s->redir.pre_fd = '%d'\n", s->redir.pre_fd);

		if (str[pos + 2] == '-')	// ('>&-')
		{
dprintf(2, "child_output_redir() -- check_duplicate() -- Found '%d>&-' CLOSING s->redir.pre_fd = '%d'\n", s->redir.pre_fd, s->redir.pre_fd);
			close(s->redir.pre_fd);
		}
		else
		{ // duplicate fd defined after '&', ('2>&1') -- this will redir stderr to stdout
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

int		child_input_redir(char *str, t_shell *s)
{
	int		pos;
	int		path;
	char	*tmp;

dprintf(2, "child_input_redir() -- \n");
	pos = get_pos(str, '<');
	s->redir.appnd = (str[pos + 1] == '<') ? 1 : 0;
	if (str[pos] == '<')
	{
		s->redir.pre_fd = STDIN_FILENO; 

		if (s->pipe.n_pipes)
			dup2(s->pipe.pipes[s->pipe.pipe_i][0], STDIN_FILENO);

		if (pos == 0)								// ('<..')
			if (!check_duplicate(str, pos, s))
				if ((path = open_output_file(s->redir.appnd, s)) > -1)
				{
					dup2(path, STDOUT_FILENO);
					close(path);
				}
		if (pos > 0 && ft_isdigit(str[pos - 1])) 	// ('2<' || '43<')
		{
			tmp = ft_strsub(str, 0, pos);
			s->redir.pre_fd = ft_atoi(tmp);
			ft_strdel(&tmp);

dprintf(2, "child_output_redir() -- '5>' -- \n");

		//	check if theres an ampersand after the redir symbol, if there is, then check whats after the ampersand
			if (!check_duplicate(str, pos, s))
				if ((path = open_output_file(s->redir.appnd, s)) > -1)
				{
					dup2(path, s->redir.pre_fd);
					close(path);
				}
		}
		if (pos == 1 && str[pos - 1] == '&')	// ('&>')
		{
			if ((path = open_output_file(s->redir.appnd, s)) > -1)
			{
				dup2(path, STDOUT_FILENO);
				dup2(path, STDERR_FILENO);
				close(path);
			}
		}
	}
	return (EXIT_SUCCESS);
}
