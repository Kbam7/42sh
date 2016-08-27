#include "ft_shell.h"

//figure out number of params

void	ft_autocomplete(t_shell *s, char *buff)
{
	if (buff[0] == 9)
	{
		if (ft_strchr(s->new_line, ' ') == NULL)
			ft_putstr("boosch");
//			ft_autocomplete_cmd(s, buff);
		else
		if (ft_strchr(s->new_line, ' ') != NULL)
			ft_autocomplete_path(s, buff);
	}
}

