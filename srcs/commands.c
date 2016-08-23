/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 14:32:15 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/23 15:58:35 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		store_commands(char *str, t_shell *s)
{
	size_t			i;
	int				ret;
	t_split_string	args;

	i = 0;
	ret = EXIT_FAILURE;
	if (str == NULL)
		return (EXIT_FAILURE);

//dprintf(2, "store_commands(), str >%s<\n", str); // debug

	if (ft_strchr(str, ';'))
	{
		args = ft_nstrsplit(str, ';');
		while (i < args.words)
		{
			ret = add_cmd(&s->commands, args.strings[i]);
			++i;
		}
		free_tab((void ***)&args.strings, args.words);
	}
	else
		ret = add_cmd(&s->commands, str);
	return (ret);
}

int		get_commands(t_shell *s)
{
	char			*cmd;
//	char			*tmp;

//dprintf(2, "get_commands(), tmp >%s<\n", tmp); // debug

	cmd = ft_strtrim(s->new_line);
//	ft_strdel(&tmp);
	if (store_commands(cmd, s) != EXIT_SUCCESS)
	{
		ft_strdel(&cmd);
		return (0);
	}
	ft_strdel(&cmd);
	return (1);
}

// This will get the string of the command and make it into input[](argv for executing commands)
void	get_input(char *cmd, t_shell *s)
{
	char			*tmp;
	t_split_string	data;

	tmp = ft_strtrim(cmd);
	data = ft_nstrsplit(tmp, ' ');
	ft_strdel(&tmp);
	s->input = ft_tabdup(data.strings, data.words);
	free_tab((void ***)&data.strings, data.words);
}
