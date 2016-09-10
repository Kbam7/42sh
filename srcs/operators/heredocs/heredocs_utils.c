/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 10:27:21 by rbromilo          #+#    #+#             */
/*   Updated: 2016/09/10 20:21:01 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_heredoc_enter(char *buff, t_shell *s)
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
			free(tmp);
		}
		if (s->new_line != NULL)
			free(s->new_line);
		s->new_line = NULL;
		s->new_line = ft_strnew(1);
		tputs(tgetstr("do", NULL), 1, ft_putchar_re);
	}	
}

static void	ft_heredoc_move_cur(char *buff, t_shell *s)
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
	ft_heredoc_enter(buff, s);
	ft_high_right(s, buff);
	ft_cut(s, buff);
	ft_cpy(s, buff);
	ft_paste(s, buff);
}

static int	ft_heredoc_buffer(t_shell *s)
{
	char	*temp;

	s->width = tgetnum("co");
    if ((temp = (char *)malloc(sizeof(char) * 4096)) == NULL)
		return (err(ERR_MALLOC, "ft_heredoc_buffer()"));
	ft_bzero(temp, 4096);
	read(0, temp, 4096);
	ft_heredoc_move_cur(temp, s);
	ft_print_char(temp, s);
	free(temp);
	return (EXIT_SUCCESS);
}

void	ft_heredoc_write(int fd, char *end, t_shell *s)
{
	while (ft_heredoc_buffer(s) == EXIT_SUCCESS)
		if (s->hdoc_newstr != NULL && s->hdoc_strlen > 0)
		{
			if (ft_strncmp(s->hdoc_newstr, end, s->hdoc_strlen - 1) == 0)
				break ;
			else
			{
				write(fd, s->hdoc_newstr, s->hdoc_strlen);
				ft_strdel(&s->hdoc_newstr);
				ft_prompt_print(s);
			}
		}
}
