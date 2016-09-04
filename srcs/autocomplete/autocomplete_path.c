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

char	*ft_getfullpath(t_shell *s, char *path)
{
	char	*ret;
	char	*cwd;
	int		path_len;

	if ((cwd = ft_getenv("PWD", s)) == NULL)
		return (NULL);
	path_len = ft_strlen(path);
	if (path[path_len - 1] == '/')
		ret = ft_strjoinstr(cwd, "/", path);
	else
		ret = ft_strjoin(cwd, "/");
	return (ret);
}

char	*ft_getpath(char **str)
{
	int		tot_len;
	int		len;
	char	*tmp;
	char	*word;

	tot_len = ft_strlen(*str);
	if ((word = ft_strrchr(*str, '/')) != NULL)
	{
		if (*(word + 1))
		{
			++word;
//dprintf(2, "ft_get_path() -- found '%c' after '/'\n", *word); // debug
			len = ft_strlen(word);
			tmp = ft_strsub(*str, 0, (tot_len - len));
			*str = ft_strdup(word);
			return (tmp);
		}
	}
	return (*str);
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
//	char			*word;
	struct stat		st;
	t_split_string	sp;
	char			*fpath;
	int				last_char;


	s->opt_i = 0;
	sp = ft_nstrsplit(s->curr, ' ');
	s->word = (sp.words > 1) ? ft_strdup(sp.strings[sp.words - 1]) : ft_strnew(0);
	s->file_path = (char *)ft_getpath(&s->word);
	last_char = ft_strlen(s->word) - 1;

//dprintf(2, "ft_select_path() -- file_path = '%s'\tword = '%s'\n", s->file_path, s->word); // debug

	if (s->word[last_char] == '/')
		s->word = ft_strnew(0);

//dprintf(2, "ft_select_path() -- file_path = '%s'\tword = '%s'\n", s->file_path, s->word); // debug

	if (s->file_path[0] != '/')
	{
		if ((fpath = ft_getfullpath(s, s->file_path)) == NULL)
			return (EXIT_FAILURE);
	}
	else
		fpath = s->file_path;


//	dprintf(2, "\nselect-path = PATH is --3-- > %s\n", path);
	if ((access(fpath, F_OK) != 0) ||
					(check_rights(fpath, 'r', 0, 'x') != EXIT_SUCCESS) ||
											((dir = opendir(fpath)) == NULL))
			return (EXIT_FAILURE);

//dprintf(2, "ft_select_path() -- fpath(opened) = '%s'\tword = '%s'\n", fpath, s->word); // debug

	while ((sd = readdir(dir)) != NULL)
	{

		if (ft_strncmp(s->word, sd->d_name, ft_strlen(s->word)) == 0)
		{
			lstat(sd->d_name, &st);
			if (ft_strcmp("cd", sp.strings[0]) == 0 && S_ISDIR(st.st_mode))
				ft_save_tab_options(s, sd->d_name);
			else
				ft_save_tab_options(s, sd->d_name);
//			if (S_ISDIR(st.st_mode))
//			{

//				free(s->tab_options[s->opt_i - 1]);
//				s->tab_options[s->opt_i - 1] = ft_strjoin(sd->d_name, "/");
//			}

		}
	}
	closedir(dir);
	ft_strdel(&fpath);
	ft_free_split(&sp);
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
//	int				stop;
	int				i;
	char			rest[3];

//	stop = ft_strlen(s->file_path);
	i = ft_strlen(s->word);
//	i = ft_strlen(s->curr);
//	i = 0;
	ft_bzero(rest, 3);
	if (s->tab_options[1] == NULL)
		while(s->tab_options[0][i] != '\0')
		{
			rest[0] = s->tab_options[0][i];
			ft_print_char(rest, s);
			++i;
		}
	else
		while (s->tab_options[0][i] != '\0' && ft_allmatch(s,i))
		{
			rest[0] = s->tab_options[0][i];
			ft_print_char(rest, s);
			++i;
		}
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
