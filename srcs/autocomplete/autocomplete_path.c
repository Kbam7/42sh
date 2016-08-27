#include "ft_shell.h"

static int		ft_select_path(t_shell *s) // saving files
{
	DIR				*dir;
	struct dirent	*sd;
	char			*tmp;
	t_split_string	sp;

	if((dir = opendir(ft_getenv("PWD", s))) == NULL)
		return (err(/*ERR_OPENDIR*/0, ft_getenv("PWD", s)));
	while ((sd = readdir(dir)) != NULL)
	{
		sp = ft_nstrsplit(s->curr, ' ');
		tmp = ft_strdup(sp.strings[sp.words - 1]);
		free_tab((void ***)sp.strings, sp.words);
		if (ft_strncmp(tmp, sd->d_name, ft_strlen(tmp)) == 0)
		{
			++s->opt_i;
			ft_save_tab_options(sd->d_name, s, sd->d_name);
		}
		ft_strdel(&tmp);
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}

void	ft_print_options(t_shell *s)
{
	int	i;

	i = 0;
	dprintf(2,"\n");
	while (i < s->opt_i)
	{
		dprintf(2, "%s\n", s->tab_options[i]);
		i++;
	}
	ft_putstr("$> ");
	ft_putstr(s->curr);
}

void	ft_autocomplete_path(t_shell *s, char *buff)
{
	ft_checkcurr(s, buff);                               // check tab count and save curr
	ft_select_path(s);										// select path from pwd
	ft_sortoptions(s);

	if (s->tab_count == 1)
		ft_putstr("BOOB");
//		ft_autocomplete(s);
	if (s->tab_count == 2)
		ft_print_options(s);
}
