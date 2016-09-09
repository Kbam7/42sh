/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 09:29:32 by tmack             #+#    #+#             */
/*   Updated: 2016/09/09 09:24:08 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"


void	ft_put_string1(t_shell *s)
{
	int		j;
	int		i;

	i = -1;
	j = 0;
	while (++i < s->curs_col)
		tputs(tgetstr("up", 0), 1, ft_putchar_re);
	tputs(tgetstr("cr", 0), 1, ft_putchar_re);
	tputs(tgetstr("cd", 0), 1, ft_putchar_re);
	ft_prompt_print(s);
	i = 0;
	while (s->new_line[i])
	{
		if (i > (s->cpy_nbr - s->a) && i <= s->cpy_nbr)
		{
			tputs(tgetstr("so", 0), 1, ft_putchar_re);
			ft_putchar(s->new_line[i]);
			tputs(tgetstr("se", 0), 1, ft_putchar_re);
			j++;
			i++;
			continue ;
		}
		ft_putchar(s->new_line[i]);
		i++;
	}
}

void	ft_high_right(t_shell *s, char *buff)
{
	if (buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 67)
	{
		s->cpy_nbr = s->curs_pos;
		s->a++;
		s->on = 1;
		ft_move_right(s, "A");
		s->on = 0;
		tputs(tgetstr("sc", 0), 1, ft_putchar_re);
		ft_put_string1(s);
		tputs(tgetstr("rc", 0), 1, ft_putchar_re);
	}
}

void	ft_paste(t_shell *s, char *buff)
{
	int		i;
	int		j;
	int		k;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = NULL;
	if (buff[0] == -53 && buff[1] == -121 && buff[2] == 0 && buff[3] == 0)
	{
		k = s->cpy_nbr - s->a;
		new_line = (char *)malloc(sizeof(char) * (s->str_len + s->a + 1));
		ft_bzero(new_line, s->str_len + (s->cpy_nbr - s->a) + 1);
		while (j < s->str_len + 1)
		{
			if (i == s->curs_pos)
			{
				while (++k <= s->cpy_nbr)
				{
					new_line[j] = s->new_line[k];
					j++;
				}
				i++;
				continue ;
			}
			new_line[j] = s->new_line[i];
			j++;
			i++;
		}
		new_line[j] = '\0';
		if (s->new_line != NULL)
			free(s->new_line);
		s->new_line = ft_strdup(new_line);
		tputs(tgetstr("sc", 0), 1, ft_putchar_re);
		ft_put_string(s);
		tputs(tgetstr("rc", 0), 1, ft_putchar_re);
		s->str_len = ft_strlen(s->new_line);
		ft_strdel(&new_line);
		s->a = 0;
		s->cpy_nbr = 0;
	}
}

void	ft_high_left(t_shell *s, char *buff)
{
	if (buff[0] == 27 && buff[1] == 27 && buff[2] == 91 && buff[3] == 68)
	{
		//	tputs(tgetstr("so", 0), 1, ft_putchar_re);
		s->on = 1;
		ft_move_left(s, "A");
		s->on = 0;
		//		tputs(tgetstr("se", 0), 1, ft_putchar_re);
	}

}
