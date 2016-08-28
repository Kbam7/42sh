#include "ft_shell.h"

void	ft_autocomplete(t_shell *s, char *buff)
{
	if (buff[0] == 9)
	{
		if (ft_strchr(s->new_line, ' ') == NULL)
			ft_putstr("boosch");
//			ft_autocomplete_cmd(s, buff);
		else
		if (ft_strchr(s->new_line, ' ') != NULL)
			ft_autocomplete_path(s);
	}
}

