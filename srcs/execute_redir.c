/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 02:00:06 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/16 22:10:18 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	open_output_file(int append, t_shell *s)
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

int		child_output_redir(char *str, t_shell *s)
{
	int		pos;
	int		path;
	char	*tmp;

dprintf(2, "child_output_redir() -- \n");
	pos = get_pos(str, '>');
	s->redir.appnd = (str[pos + 1] == '>') ? 1 : 0;
	if (str[pos] == '>')
	{
		s->redir.pre_fd = STDOUT_FILENO; 

		if (s->pipe.n_pipes)
			dup2(s->pipe.pipes[s->pipe.pipe_i][0], STDIN_FILENO);

		if (pos == 0)	// ('>..')
			if (!check_duplicate(str, pos, s))
				if ((path = open_output_file(s->redir.appnd, s)) > -1)
				{
					dup2(path, STDOUT_FILENO);
					close(path);
				}
		if (pos > 0 && ft_isdigit(str[pos - 1])) // ('2>' || '43>')
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

/*
int		child_output_redir(char *str, t_shell *s)
{
	// execute this inside child process
	// this function must be executed just before executing the command

	//	find the type of  redir, 
	//	if theres a fd defined, output to the fd or redirect the fd depending on the reder string
	// write output to pipe[i + 1]
	int		i;
	int		pos;
	int		path;
	char	*tmp;

	i = s->redir.rdr_i;
	pos = get_pos(str, '>');
	if (str[pos] == '>')
	{
		s->redir.pre_fd = STDOUT_FILENO; 

		if ((path = open(s->redir.cmd[i + 1], O_WRONLY | O_CREAT |
					((str[pos + 1] == '>') ? O_APPEND : O_TRUNC), 0664)) < 0) // S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
			return (err(ERR_CREATE, s->redir.cmd[i + 1]));

		if (pos == 1 && str[pos - 1] == '&')	// ('&>')
		{
			dup2(path, STDOUT_FILENO);
			dup2(path, STDERR_FILENO);
		}
		else if (pos > 0 && ft_isdigit(str[pos - 1])) // ('2>' || '43>')
		{
			tmp = ft_strsub(str, 0, pos);
			s->redir.pre_fd = ft_atoi(tmp);
			ft_strdel(&tmp);
			dup2(path, s->redir.pre_fd);
		}
		else if (pos == 0)	// ('>..')
		{
			if (s->pipe.n_pipes && s->redir.rdr_i == 0)
				dup2(s->pipe.pipes[s->pipe.pipe_i][0], STDIN_FILENO);
			dup2(path, STDOUT_FILENO);
		}
		if (str[pos + 1] == '>')	// ('>>')
			++pos;
		if (str[pos + 1] == '&')	// ('>&')
		{
			if (str[pos + 2] == '-')	// ('>&-')
				close(s->redir.pre_fd);
			else
			{ // duplicate fd defined after '&', ('2>&1') -- this will redir stderr to stdout
				tmp = ft_strsub(str, (pos + 2), (ft_strlen(str) - (pos + 2)));
				s->redir.post_fd = ft_atoi(tmp);
				ft_strdel(&tmp);
				dup2(s->redir.post_fd, s->redir.pre_fd);
			}
		}
		close(path);
	}
	return (EXIT_SUCCESS);
}
*/
