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
		if ((tmp = ft_tabdup(s->tab_options, i + 1)) == NULL)
			return (err(ERR_MALLOC, "ft_save_tab_options()"));
		else
		{
			free_tab((void ***)&s->tab_options, i);
			s->tab_options = tmp;
			s->tab_options[i] = ft_strdup(d_name);
		}
//	dprintf(2, "tab_options is --------> %s \n", s->tab_options[s->opt_i]);
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
			if (s->tab_options[k][j] > s->tab_options[i][j])
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
