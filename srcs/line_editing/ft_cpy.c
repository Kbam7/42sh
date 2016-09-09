/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 09:29:32 by tmack             #+#    #+#             */
/*   Updated: 2016/09/09 13:11:19 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_paste_1(t_shell *s, char *new_line)
{
	int		i;
	int		j;
	int		len;
	int		k;

	k = 0;
	j = 0;
	i = 0;
	len = ft_strlen(s->cpy_cut);
	while (k <= s->str_len)
	{
		if (k == s->curs_pos)
		{
			while (s->cpy_cut[j])
			{
				new_line[i] = s->cpy_cut[j];
				j++;
				i++;
			}
		}
		new_line[i] = s->new_line[k];
		i++;
		k++;
	}
}

void	ft_paste(t_shell *s, char *buff)
{
	char	*new_line;

	new_line = NULL;
	if (buff[0] == 16 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
	{
		new_line = ft_strnew(s->str_len + ft_strlen(s->cpy_cut) + 1);
		ft_bzero(new_line, s->str_len + ft_strlen(s->cpy_cut) + 1);
		ft_paste_1(s, new_line);
		free(s->new_line);
		s->new_line = ft_strdup(new_line);
		s->str_len = ft_strlen(s->new_line);
		tputs(tgetstr("sc", 0), 1, ft_putchar_re);
		ft_put_string(s);
		tputs(tgetstr("rc", 0), 1, ft_putchar_re);
		ft_strdel(&new_line);
	}
}

void    ft_cpy(t_shell *s, char *buff)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (buff[0] == 25 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0)
	{
		if (s->cpy_cut != NULL)
			free(s->cpy_cut);
		s->cpy_cut = ft_strnew(s->a + 1);
		ft_bzero(s->cpy_cut, s->a + 1);
		while (j < s->str_len + 1)
		{
			if (j == (s->cpy_nbr - s->a) + 1)
				while (k < s->a)
				{
					s->cpy_cut[k] = s->new_line[j];
					k++;
					j++;
				}
			j++;
		}
		s->a = 0;
		s->cpy_nbr = 0;
	}
}
