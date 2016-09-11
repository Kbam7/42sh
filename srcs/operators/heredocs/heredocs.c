/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 14:27:46 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 18:05:56 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	ft_heredoc_rw(int fd, t_shell *s)
{
	char	*end;
	int		i;

	ft_prompt_new("heredoc> ", s);
	ft_putstr(s->prompt);
	i = s->redir.rdr_i;
	end = s->redir.cmd[i + 1];
	ft_heredoc_write(fd, end, s);
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (err(0, "heredoc"));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int			ft_heredocs(t_shell *s)
{
	char	tmp_name[32];
	int		fd;

	s->hdoc_newstr = NULL;
	ft_memset(tmp_name, 0, 32);
	ft_strncpy(tmp_name, "/tmp/42sh_heredoc-XXXXXX", 28);
	fd = mkstemp(tmp_name);
	unlink(tmp_name);
	if (fd < 0)
		return (err(ERR_CREATE, "heredoc"));
	return (ft_heredoc_rw(fd, s));
}
