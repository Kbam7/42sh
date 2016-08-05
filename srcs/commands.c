/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/30 23:16:38 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/05 07:37:49 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	store_commands(char *str, t_shell *s)
{
	size_t			i;
	int				ret;
	t_split_string	args;

	i = 0;
	ret = EXIT_FAILURE;
	if (ft_strchr(str, ';'))
	{
		args = ft_nstrsplit(str, ';');
		while (i < args.words)
		{
			ret = add_cmd(&s->commands, args.strings[i]);
			++i;
		}
		free_tab((void **)args.strings, args.words);
	}
	else
		ret = add_cmd(&s->commands, str);
	return (ret);
}

int		get_commands(t_shell *s)
{
	char			*cmd;
	int				ret;
	char			*tmp;

	if ((ret = ft_gnl(0, &tmp)) > 0)
	{
		cmd = ft_strtrim(tmp);
		ft_strdel(&tmp);
		if (store_commands(cmd, s) != EXIT_SUCCESS)
		{
			ft_strdel(&cmd);
			return (0);
		}
		ft_strdel(&cmd);
	}
	if (ret < 0)
		return (err(ERR_GNL, "ft_gnl Error!"));
	return (ret);
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
	free_tab((void **)data.strings, data.words);
}
