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
			++s->opt_i;
			ft_save_tab_options(s, sd->d_name);
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
	ft_putstr("\n");
	while (i < s->opt_i)
	{
		ft_putstr(s->tab_options[i]);
		ft_putstr("\n");
		i++;
	}
	ft_putstr("$> ");
	ft_putstr(s->curr);
}

void	ft_autocomplete_path(t_shell *s)
{
	ft_checkcurr(s);                               // check tab count and save curr
	ft_select_path(s);										// select path from pwd
	ft_sortoptions(s);

	if (s->tab_count == 1)
		ft_putstr("BOOB");
//		ft_autocomplete(s);
	if (s->tab_count == 2)
		ft_print_options(s);
}
