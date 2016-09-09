#include "ft_shell.h"

static int	ft_allmatch(t_shell *s, int stop)
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

void		ft_print_options(t_shell *s)
{
	int				i;

	i = 0;
	while (i <= s->opt_i - 1)
	{
		ft_putendl(s->tab_options[i]);
		i++;
	}
	ft_prompt_print(s);
	ft_putstr(s->curr);
}

void		ft_print_word(t_shell *s)
{
	int				i;
	char			rest[3];

	i = ft_strlen(s->word);
	ft_bzero(rest, 3);
	if (s->tab_options[1] == NULL)
		while(s->tab_options[0][i] != '\0')
		{
			if (s->tab_options[0][i] == ' ')
			{
				rest[0] = '\\';
				ft_print_char(rest, s);
			}
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


