/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 10:27:21 by rbromilo          #+#    #+#             */
/*   Updated: 2016/09/06 10:27:22 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_autocomplete_path(t_shell *s)
{
	ft_checkcurr(s);
	if (s->tab_count == 1 && ft_strlen(s->new_line) > 0)
	{
		if (s->tab_options != NULL)
		{
			free_tab((void ***)&s->tab_options, s->opt_i);
			s->opt_i = 0;
		}
		if (ft_strchr(s->new_line, ' ') != NULL)
			ft_select_path(s);
		else if (ft_strchr(s->new_line, ' ') == NULL)
			ft_select_cmd(s);
		if (s->tab_options != NULL)
		{
			ft_sortoptions(s);
			ft_print_word(s);
		}
	}
	if (s->tab_count == 2)
	{
		if (s->tab_options != NULL)
		{
			ft_putchar('\n');
			ft_print_options(s);
		}
	}
}

int		ft_select_cmd(t_shell *s)
{
	DIR				*dir;
	struct dirent	*sd;
	char			*tmp;
	int				i;

	i = 0;
	s->word = ft_strdup(s->new_line);
	while((dir = opendir(s->paths[i])) != NULL)
	{
		if (access(s->paths[i], F_OK) == 0)
			while ((sd = readdir(dir)) != NULL)
				if (ft_strncmp(s->curr, sd->d_name, ft_strlen(s->curr)) == 0)
				{
					tmp = ft_strjoin(sd->d_name, " ");
					ft_save_tab_options(s, tmp);
					ft_strdel(&tmp);
				}
		++i;
	}
	if (dir == NULL)
		return (err(/*ERR_OPENDIR*/0, s->paths[i]));
	closedir(dir);
	return (EXIT_SUCCESS);
}

void	ft_autocomplete(t_shell *s, char *buff)
{
	if (buff[0] == 9)
	{
		ft_autocomplete_path(s);
	}
	ft_strdel(&s->word);
}
