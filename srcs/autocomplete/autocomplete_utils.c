#include "ft_shell.h"

void	ft_checkcurr(t_shell *s)
{
	char	*tmp;

	if (s->curr == NULL)
	{
		s->curr = ft_strdup(s->new_line);
		s->tab_count = 1;
	}
	else if (s->curr && ft_strcmp(s->curr, s->new_line) != 0)
	{
		s->tab_count = 1;
		tmp = ft_strdup(s->new_line);
		ft_strdel(&s->curr);
		s->curr = tmp;
	}

	else if (s->curr && ft_strcmp(s->curr, s->new_line) == 0)
		s->tab_count = 2;
	s->cmd_len = ft_strlen(s->curr);
}

int	ft_save_tab_options(t_shell *s, char *d_name)
{
	int		i;
	char	**tmp;

	i = s->opt_i;	

	if (i == 0)
	{
		if ((s->tab_options = (char **)malloc(sizeof(char *) * 2)) == NULL)
				return (err(ERR_MALLOC, "ft_save_tab_options()"));
		else
		{
			s->tab_options[0] = ft_strdup(d_name);
			s->tab_options[1] = NULL;
		}
	}
	else if (i > 0)
	{
		if ((tmp = ft_tabdup(s->tab_options, i + 2)) == NULL)
			return (err(ERR_MALLOC, "ft_save_tab_options()"));
		else
		{
		free_tab((void ***)&s->tab_options, i);
			s->tab_options = tmp;
			s->tab_options[i] = ft_strdup(d_name);
		}
//	dprintf(2, "d_name is ----- %s \t tab_options is --------> %s \n", d_name, s->tab_options[i]);
	}
	return (EXIT_SUCCESS);
}

void	ft_sortoptions(t_shell *s)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;


	k = 0;
	while (k < s->opt_i)
	{
		i = k + 1;
		j = 0;
		while (i < s->opt_i)
		{
			while (s->tab_options[k][j] == s->tab_options[i][j])
					j++;
			if (s->tab_options[k][j] < s->tab_options[i][j])
			{
					tmp = s->tab_options[k];
					s->tab_options[k] = s->tab_options[i];
					s->tab_options[i] = tmp;

			}
			j = 0;
			i++;
		}
		k++;
	}
}
/*
void	ft_complete_word(t_shell *s)
{
	int			i;
	int			k;
	char		*buff;
	int			j;
	int			h;

	i = 0;
	j = s->cmd_len;
	k = 0;
	h = 0;
	if (s->tab_options[i + 1] == NULL && i == 0)
	{
		while (s->tab_options[i][j] != '\0') // up to end of line or up the j(position of fork)
		{
			buff = (char *)ft_memalloc(sizeof(char) * 4);
			ft_print_char(buff, s);
			j++;
		}
	}
	else
	{
		while (s->tab_options[i] && h != 1)
		{
			while (s->tab_options[i][k] != '\0' )	// finding value for cmd_fork
			{
				if (s->tab_options[i][k] != s->tab_options[i + 1][k])
				{
					h = 1;
					break ;
				}
				k++;
			}
			if (h == 1)
			{
				s->cmd_fork = k;
				break ;
			}
			++i;
		}
	}
}
*/
