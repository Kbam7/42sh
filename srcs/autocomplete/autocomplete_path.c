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
	if (s->opt_i > 30)
	{
		ft_putstr("are you sure you want to display all ");
		ft_putnbr(s->opt_i);
		ft_putstr("possabilities? (y or n)");
	}
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
	while (s->tab_options[i + 1] != NULL)
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
	i = ft_strlen(tmp);
	while(s->tab_options[1][i] != '\0' && ft_allmatch(s,i))
	{
		rest[0] = s->tab_options[1][i];
		rest[1] = 0;
		rest[2] = 0;
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
		ft_sortoptions(s);
		ft_print_word(s);
	}
	if (s->tab_count == 2)
	{
		ft_putchar('\n');
		ft_print_options(s);
	}
}
