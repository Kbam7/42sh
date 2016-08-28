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

static int		ft_select_path(t_shell *s) // saving files
{
	DIR				*dir;
	struct dirent	*sd;
	char			*tmp;
	t_split_string	sp;

	if((dir = opendir(ft_getenv("PWD", s))) == NULL)
		return (err(/*ERR_OPENDIR*/0, ft_getenv("PWD", s)));
	sp = ft_nstrsplit(s->curr, ' ');
	tmp = ft_strdup(sp.strings[sp.words - 1]);
	ft_free_split(&sp);
	while ((sd = readdir(dir)) != NULL)
	{
		if (ft_strncmp(tmp, sd->d_name, ft_strlen(tmp)) == 0)
		{
			ft_save_tab_options(s, sd->d_name);
//			dprintf(2, "tab-option == %s \t d_name == %s /n", s-tab_options[i]);
			s->opt_i++;
		}
	}
	ft_strdel(&tmp);
	closedir(dir);
	return (EXIT_SUCCESS);
}

void	ft_print_options(t_shell *s)
{
	int	i;

	i = 0;
	while (i < s->opt_i)
	{
		ft_putendl(s->tab_options[i]);
		i++;
	}

	ft_putstr("$>");
	ft_putstr(s->curr);
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
	i = ft_strlen(tmp);
	while(s->tab_options[1][i] != '\0')
	{
		rest[0] = s->tab_options[1][i];
		rest[1] = 0;
		rest[2] = 0;
		ft_print_char(rest, s);
		i++;
	}
//	ft_strdel(rest);
	ft_strdel(&tmp);
}

void	ft_autocomplete_path(t_shell *s)
{
	ft_checkcurr(s);
	if (s->tab_count == 1)
	{
		ft_select_path(s);
		ft_sortoptions(s);
		ft_print_word(s);
	}
//		ft_autocomplete(s);
	if (s->tab_count == 2)
	{
		ft_putchar('\n');
		ft_print_options(s);
	}
}

