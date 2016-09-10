/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 14:27:46 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/10 20:20:45 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	ft_heredoc_rw(int fd, t_shell *s)
{
	char	*end;
	int		i;

	ft_prompt_new("heredoc> ", s);
	ft_prompt_print(s);
	i = s->redir.rdr_i;
	end = s->redir.cmd[i + 1];
	ft_heredoc_write(fd, end, s);
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (err(/*ERR_LSEEK*/0, "heredoc"));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int		ft_heredocs(t_shell *s)
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
