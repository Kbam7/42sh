/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 10:27:21 by rbromilo          #+#    #+#             */
/*   Updated: 2016/09/11 11:06:51 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	ft_autocomplete_path(t_shell *s)
{
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

char		*ft_getpath(char **str)
{
	int		tot_len;
	int		len;
	char	*tmp;
	char	*word;

	word = NULL;
	tot_len = ft_strlen(*str);
	if ((*str)[0])
	{
		if (ft_strchr(*str, '/') && (word = ft_strrchr(*str, '/')) != NULL)
			if (*(word + 1))
			{
				++word;
				len = ft_strlen(word);
				tmp = ft_strsub(*str, 0, (tot_len - len));
				*str = ft_strdup(word);
				return (tmp);
			}
	}
	return (*str);
}

int			ft_select_cmd(t_shell *s)
{
	DIR				*dir;
	struct dirent	*sd;
	char			*tmp;
	int				i;

	i = 0;
	s->word = ft_strdup(s->new_line);
	while ((dir = opendir(s->paths[i])) != NULL)
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
		return (err(ERR_OPENDIR, s->paths[i]));
	closedir(dir);
	return (EXIT_SUCCESS);
}

void		ft_autocomplete(t_shell *s, char *buff)
{
	if (buff[0] == 9)
	{
		ft_checkcurr(s);
		ft_autocomplete_path(s);
	}
	ft_strdel(&s->word);
}
