#include "ft_shell.h"

void	ft_autocomplete(t_shell *s, char *buff)
{
	if (buff[0] == 9)
	{
			ft_autocomplete_path(s);
	//	else
	//		ft_autocomplete_cmd(s);
	}
}

