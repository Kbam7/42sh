/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 14:27:46 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/01 17:44:48 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_heredoc_move_cur(char *buff, t_shell *s)
{
	ft_move_down(s, buff);
	ft_move_up(s, buff);
	ft_left_word(s, buff);
	ft_right_word(s, buff);
	ft_move_left(s, buff);
	ft_move_right(s, buff);
	ft_backspace(s, buff);
	ft_ctrl_l(buff);
	ft_end_right(s, buff);
	ft_end_left(s, buff);
	ft_heredoc_enter(buff, s);
}

void	ft_heredoc_buffer(t_shell *s)
{
	char	*temp;

	s->width = tgetnum("co");
    temp = (char *)malloc(sizeof(char) * 4096);
	ft_bzero(temp, 4096);
	read(0, temp, 4096);
	ft_move_cur(temp, s);
	ft_print_char(temp, s);
	free(temp);
}

static int	ft_heredoc_rw(int fd, t_shell *s)
{
	char	*line;
	int		ret;
	int		i;


	line = NULL;
	ft_putstr(" heredoc> ");
	i = s->redir.rdr_i;
dprintf(2, "ft_heredoc() - ft_heredoc_rw() -- cmd[%d] = '%s'\tcmd[%d] = '%s'\n", i, s->redir.cmd[i], i+1, s->redir.cmd[i+1]); // debug
	while ((ret = ft_gnl(0, &line)) > 0)
	{
dprintf(2, "ft_heredoc() - ft_heredoc_rw() -- inside gnl loop -- line = '%s'\n", line); // debug
		if (ft_strncmp(line, s->redir.cmd[i + 1], ft_strlen(line)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		ft_strdel(&line);
		ft_putstr(" heredoc> ");
	}
	ft_strdel(&line);
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (err(/*ERR_LSEEK*/0, "heredoc"));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int		ft_heredocs(char *str, int pos, t_shell *s)
{
	char	tmp_name[32];
	int		fd;

	ft_memset(tmp_name, 0, sizeof(tmp_name));
	if (str[pos] == str[pos + 2])			// '<<<'
	{
		// herestring reads one word or until end quote is found
	}
	else
	{
//		path = open(".42sh_heredoc", O_RDWR | O_CREAT, 0664); // S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
//		path = open(ft_getenv("PWD", s), O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);

		ft_strncpy(tmp_name, "/tmp/tmp.42sh.heredoc-XXXXXX", 28);
		fd = mkstemp(tmp_name);
		unlink(tmp_name);
		if (fd < 0)
			return (err(ERR_CREATE, "heredoc"));
		return (ft_heredoc_rw(fd, s));
	}
	return (EXIT_SUCCESS);
}
