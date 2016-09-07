/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbromilo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 10:27:15 by rbromilo          #+#    #+#             */
/*   Updated: 2016/09/06 12:06:10 by rbromilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	*ft_getfullpath(t_shell *s, char *path)
{
	char	*ret;
	char	*cwd;
	int		path_end;

	if ((cwd = ft_getenv("PWD", s)) == NULL)
		return (NULL);
	path_end = (path[0]) ? ft_strlen(path) - 1 : 0;
	if (path[path_end] == '/')
		ret = ft_strjoinstr(cwd, "/", path);
	else
		ret = ft_strjoin(cwd, "/");
	return (ret);
}

static char	*ft_getpath(char **str)
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

static void	ft_chksv(struct stat *st, struct dirent *sd, char *str, t_shell *s)
{
	char			*tmp;

	tmp = NULL;
	if (ft_strcmp("cd", str) == 0)
	{
		if (S_ISDIR(st->st_mode))
		{
			tmp = ft_strjoin(sd->d_name, "/");
			ft_save_tab_options(s, tmp);
		}
	}
	else
	{
		if (S_ISDIR(st->st_mode))
		{
			tmp = ft_strjoin(sd->d_name, "/");
			ft_save_tab_options(s, tmp);
		}
		else
		{
			tmp = ft_strjoin(sd->d_name, " ");
			ft_save_tab_options(s, tmp);
		}
	}
	ft_strdel(&tmp);
}

static void	ft_search_save(t_shell *s, char	**fp, t_split_string *sp)
{
	struct dirent	*sd;
	struct stat		st;
	char			*extpath;
	DIR				*dir;

	if ((access(*fp, F_OK) != 0) || (dir = opendir(*fp)) == NULL)
			return ;
	while ((sd = readdir(dir)) != NULL)
	{
		extpath = ft_strjoin(*fp, sd->d_name);
		lstat(extpath, &st);
		if ((ft_strncmp(s->word, sd->d_name, ft_strlen(s->word)) == 0 ||
							ft_strlen(s->word) == 0) && sd->d_name[0] != '.')
		{
			ft_chksv(&st, sd, sp->strings[0], s);
		}
		ft_strdel(&extpath);
	}
	ft_strdel(fp);
	ft_free_split(sp);
	closedir(dir);
}


int		ft_select_path(t_shell *s)
{
	t_split_string	sp;
	char			*fpath;
	int				last_char;

	s->opt_i = 0;
	sp = ft_nstrsplit(s->curr, ' ');
	s->word = (sp.words > 1) ? ft_strdup(sp.strings[sp.words - 1]) :
																ft_strnew(0);
	s->file_path = (char *)ft_getpath(&s->word);
	last_char = (s->word[0]) ? ft_strlen(s->word) - 1 : 0;
	if (s->word[0] && s->word[last_char] == '/')
		s->word = ft_strnew(0);
	if (s->file_path[0] != '/')
	{
		if ((fpath = ft_getfullpath(s, s->file_path)) == NULL)
			return (EXIT_FAILURE);
	}
	else
		fpath = s->file_path;
	ft_search_save(s, &fpath, &sp);
	return (EXIT_SUCCESS);
}
