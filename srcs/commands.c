/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 14:32:15 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/28 16:14:37 by kbamping         ###   ########.fr       */
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

	cmd = ft_strtrim(s->new_line);
	ft_strdel(&s->new_line);
	if (store_commands(cmd, s) != EXIT_SUCCESS)
	{
		ft_strdel(&cmd);
		return (0);
	}
	ft_strdel(&cmd);
	return (1);
}
