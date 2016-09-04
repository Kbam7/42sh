/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 14:27:46 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/03 21:22:23 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_heredoc_enter(char *buff, t_shell *s)
{
	char	*tmp;

	if (buff[0] == 10 && buff[1] == 0 && buff[2] == 0)
	{
		ft_new_history(s);
		s->curs_pos = 0;
		s->str_len = 0;
		s->h_pos = 0;
		if (s->new_line != NULL && ft_strlen(s->new_line) > 0)
		{
			tmp = ft_strjoin(s->new_line, "\n");
			ft_strdel(&s->new_line);
			s->hdoc_newstr = ft_strdup(tmp);
			s->hdoc_strlen = ft_strlen(s->hdoc_newstr);
		}
		if (s->new_line != NULL)
			free(s->new_line);
		s->new_line = NULL;
		s->new_line = ft_strnew(1);
	}	
}

void	ft_heredoc_move_cur(char *buff, t_shell *s)
{
	ft_move_down(s, buff);
	ft_move_up(s, buff);
	ft_left_word(s, buff);
	ft_right_word(s, buff);
	ft_move_left(s, buff);
	ft_move_right(s, buff);
	ft_backspace(s, buff);
	ft_ctrl_l(buff, s);
	ft_history_up(s, buff);
	ft_history_down(s, buff);
	ft_end_right(s, buff);
	ft_end_left(s, buff);
	ft_autocomplete(s, buff);
	ft_heredoc_enter(buff, s);
}

static int	ft_heredoc_buffer(t_shell *s)
{
	char	*temp;

	s->width = tgetnum("co");
    if ((temp = (char *)malloc(sizeof(char) * 24)) == NULL)
		return (err(ERR_MALLOC, "ft_heredoc_buffer()"));
	ft_bzero(temp, 24);
	read(0, temp, 24);
	ft_heredoc_move_cur(temp, s);
	ft_print_char(temp, s);
	free(temp);
	return (EXIT_SUCCESS);
}

static int	ft_heredoc_rw(int fd, t_shell *s)
{
	char	*end;
	int		i;


	ft_putstr(" heredoc> ");
	i = s->redir.rdr_i;
	end = s->redir.cmd[i + 1];
	while (ft_heredoc_buffer(s) == EXIT_SUCCESS)
		if (s->hdoc_newstr != NULL && s->hdoc_strlen > 0)
		{
			if (ft_strncmp(s->hdoc_newstr, end, s->hdoc_strlen - 1) == 0)
				break ;
			else
			{
			// Add a check here that will remove any preceding tabulations if '<<-'
				write(fd, s->hdoc_newstr, s->hdoc_strlen);
				ft_strdel(&s->hdoc_newstr);
				ft_putstr(" heredoc> ");
			}
		}
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

	s->hdoc_newstr = NULL;
	ft_memset(tmp_name, 0, 32);
	if (str[pos] == str[pos + 2])			// '<<<'
	{
		// herestring reads one word or until end quote is found
	}
	else
	{
		ft_strncpy(tmp_name, "/tmp/42sh_heredoc-XXXXXX", 28);
		fd = mkstemp(tmp_name);
		unlink(tmp_name);
		if (fd < 0)
			return (err(ERR_CREATE, "heredoc"));
		return (ft_heredoc_rw(fd, s));
	}
	return (EXIT_SUCCESS);
}
