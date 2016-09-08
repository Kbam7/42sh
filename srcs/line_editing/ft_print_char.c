/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 14:08:49 by tmack             #+#    #+#             */
/*   Updated: 2016/09/07 09:16:07 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_insert(t_shell *s, char buff)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char *)malloc(sizeof(char) * (s->str_len + 2));
	ft_bzero(temp, s->str_len + 2);
	if (s->new_line != NULL)
		temp = ft_strcpy(temp, s->new_line);
	if (s->curs_pos != s->str_len)
	{
		i = s->str_len;
		while (i >= s->curs_pos)
		{
			temp[i + 1] = temp[i];
			i--;
		}
		temp[s->curs_pos] = buff;
	}
	else if (buff)
		temp[s->str_len] = buff;
	free(s->new_line);
	s->new_line = NULL;
	s->new_line = ft_strdup(temp);
	free(temp);
}

void	ft_put_string(t_shell *s)
{
	int		i;

	i = 0;
	while (i < s->curs_col)
	{
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
		i++;
	}
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	tputs(tgetstr("cd", 0), 1, ft_putchar_re);
	ft_prompt_print(s);
	ft_putstr(s->new_line);
}

void	ft_put_curs(t_shell *s)
{
	int		i;

	i = (s->cols) - s->curs_col;
	while (i-- > 0)
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	if ((s->curs_pos + s->prompt_len + 1) % (s->width) == 0)
	{
		tputs(tgetstr("do", 0), 1, ft_putchar_re);
		i = 0;
	}
	else if (s->cols == 0)
		i = ft_curs_pos(s) + s->prompt_len + 1;
	else
		i = ft_curs_pos(s);
	while (i-- > 0)
		tputs(tgetstr("nd", 0), 1, ft_putchar_re);
}

void	ft_print_char(char *buff, t_shell *s)
{
	if (buff[0] >= 32 && buff[0] <= 126 && buff[1] == 0 && buff[2] == 0)
	{
		ft_nbr_cols(s);
		ft_curs_col(s);
		ft_insert(s, buff[0]);
		ft_put_string(s);
		ft_put_curs(s);
		s->curs_pos++;
		s->str_len++;
		s->new_line[s->str_len] = '\0';
	}
}

void	ft_enter(char *buff, t_shell *s)
{
	if (buff[0] == 10 && buff[1] == 0 && buff[2] == 0)
	{
		ft_putchar('\n');
		ft_check_wait(s);
		ft_new_history(s);
		s->curs_pos = 0;
		s->str_len = 0;
		s->h_pos = 0;
		if (!get_commands(s))
			ft_prompt_print(s);
		if (s->new_line != NULL || s->new_line[0] != '\0')
			free(s->new_line);
		s->new_line = NULL;
		s->new_line = (char *)malloc(sizeof(char) + 1);
		s->new_line[0] = '\0';
	}
}
