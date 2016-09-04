#include "ft_shell.h"

static void		ft_free_split(t_split_string *sp)
{
	size_t	i;

	i = 0;
	while (i < sp->words)
	{
		ft_strdel(&sp->strings[i]);
		++i;
	}
	free(sp->strings);
	sp->strings = NULL;
}

char	*ft_getpath(t_shell *s, char *path)
{
	char			*ret;
	char			*tmp;

	tmp = ft_strdup(ft_getenv("PWD", s));
	ret = ft_strdup(tmp);
	if (path[0] != '\0')
		ret = ft_strjoinstr(ret,"/",path);
	ret = ft_strjoin(ret, "/");
	free(tmp);
//	if (pat)
//		ret = ft_strjoinstr(ret, "/", path);
//	if (!path)
//		ret = ft_strjoinstr(ret, path,"/");
	return (ret);
}

char	*ft_addpath(char *str)
{
	int		tot_len;
	int		len;
	char	*tmp;

	tot_len = ft_strlen(str);
	if ((tmp = ft_strrchr(str, '/') + 1) == NULL)
		return (str);
	len = ft_strlen(tmp);
	tmp = ft_strsub(str, 0, (tot_len - len));
	return (tmp);
/*
	t_split_string			backslash;
	unsigned int			i;
	char					*ret;

	backslash = ft_nstrsplit(str, '/');
	i = 0;
	ret = ft_strnew(0);
	while (i + 1 != backslash.words)
	{
		if (i > 0 && i + 1 != backslash.words)
			ret = ft_strjoinstr(ret,"/", backslash.strings[i]);
		else
			ret = ft_strjoin(ret, backslash.strings[i]);
		i++;
	}
	ft_free_split(&backslash);
	return (ret);
*/
}

static int		ft_select_path(t_shell *s) // saving files
{
	DIR				*dir;
	struct dirent	*sd;
	char			*tmp;
	char			*tmp2;
	struct stat		st;
	t_split_string	space;
	unsigned int		i;
	char			*path;
	char			*pathend;


	space = ft_nstrsplit(s->curr, ' ');
	tmp = ft_strdup(space.strings[space.words - 1]);
	pathend = (char *)ft_addpath(tmp);
	if (ft_strchr(tmp, '/'))
	{
		tmp2 = ft_strdup(ft_strrchr(tmp, '/'));
		s->tmp2_len = ft_strlen(tmp2) - 1;
		free(tmp);
		i = 0;
		tmp = malloc(sizeof(char )* ft_strlen(tmp2) - 1);
		while(i < ft_strlen(tmp2))
		{
			tmp[i] = tmp2 [i + 1];
			i++;
		}
		free(tmp2);
	}
	else
		s->tmp2_len = ft_strlen(tmp);
	path = ft_getpath(s,pathend);
	s->opt_i = 0;
//	dprintf(2, "\nselect-path = PATH is --3-- > %s\n", path);
	if((dir = opendir(path)) == NULL)
		return (err(/*ERR_OPENDIR*/0, path));
	while ((sd = readdir(dir)) != NULL)
	{

		if (ft_strncmp(tmp, sd->d_name, ft_strlen(tmp)) == 0)
		{
		lstat(sd->d_name, &st);
//			if (ft_strcmp("cd", space.strings[0]) == 0 && S_ISDIR(st.st_mode))
//			{
//		dprintf(2, "2");
				ft_save_tab_options(s, sd->d_name);
				s->opt_i++;
//			}
//			else if (!(ft_strcmp("cd", space.strings[0]) == 0))
//			{
//		dprintf(2, "3");
//				ft_save_tab_options(s, sd->d_name);
//				s->opt_i++;
//			}
//			if (S_ISDIR(st.st_mode))
//			{
//		dprintf(2, "4");
//				free(s->tab_options[s->opt_i - 1]);
//				s->tab_options[s->opt_i - 1] = ft_strjoin(sd->d_name, "/");
//			}

		}
	}
	ft_strdel(&path);
	ft_strdel(&pathend);
	ft_free_split(&space);
	ft_strdel(&tmp);
	closedir(dir);
	return (EXIT_SUCCESS);
}

void	ft_print_options(t_shell *s)
{
	int	i;

	i = 0;
/*	if (s->opt_i > 30)
	{
		ft_putstr("are you sure you want to display all ");
		ft_putnbr(s->opt_i);
		ft_putstr("possabilities? (y or n)");
	}
*/
	while (i <= s->opt_i - 1)
	{
		ft_putendl(s->tab_options[i]);
		i++;
	}

	ft_putstr("$>");
	ft_putstr(s->curr);
}

int		ft_allmatch(t_shell *s, int stop)
{
	int	i;

	i = 0;
	while (s->tab_options[i] && s->tab_options[i + 1] != NULL)
	{
		 if (s->tab_options[i][stop] != s->tab_options[i + 1][stop])
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_word(t_shell *s)
{
	int				i;
	char			*tmp;
	t_split_string	sp;
	char			rest[3];

	sp = ft_nstrsplit(s->curr, ' ');
	tmp = ft_strdup(sp.strings[sp.words - 1]);
	ft_free_split(&sp);
	i = s->tmp2_len;
	ft_bzero(rest, 3);
	while(s->tab_options[0][i] != '\0' && ft_allmatch(s,i))
	{
		rest[0] = s->tab_options[0][i];
		ft_print_char(rest, s);
		i++;
	}
	ft_strdel(&tmp);
}

static int		ft_select_cmd(t_shell *s)
{
	DIR				*dir;
	struct dirent	*sd;
	char			*tmp;
	int				i;

	i = 0;
	while((dir = opendir(s->paths[i])) != NULL)
	{
		if (access(s->paths[i], F_OK) == 0)
		{
			while ((sd = readdir(dir)) != NULL)
			{
				if (ft_strncmp(s->curr, sd->d_name, ft_strlen(s->curr)) == 0)
				{

					ft_save_tab_options(s, sd->d_name);
					s->opt_i++;

				}
			}
		}
		++i;
	}
	if (dir == NULL)
		return (err(/*ERR_OPENDIR*/0, s->paths[i]));
	ft_strdel(&tmp);
	closedir(dir);
	return (EXIT_SUCCESS);
}


void	ft_autocomplete_path(t_shell *s)
{
	ft_checkcurr(s);
	if (s->tab_count == 1)
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
