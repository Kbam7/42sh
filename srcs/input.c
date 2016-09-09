/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 09:59:03 by kgani             #+#    #+#             */
/*   Updated: 2016/09/09 11:35:37 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	process_input(char *cmd, t_shell *s)
{
	int		error;
	char 	*ret;

	error = EXIT_FAILURE;

	if (!ft_check_inhibitors(cmd))
	{
		if ((ret = ft_strstr(cmd, "||")))
			return (process_logical_or(cmd, s));
		if ((ret = ft_strstr(cmd, "&&")))
			return (process_logical_and(cmd, s));
		if (ft_strchr(cmd, '|'))
			return (process_pipes(cmd, s));
		if (ft_strchr(cmd, '<') || ft_strchr(cmd, '>'))
			return (process_redir(cmd, s));
		else
		{
			if (s->input != NULL)
				free_tab((void ***)&s->input, ft_tablen(s->input));
			get_input(cmd, s);
			error = execute_cmd(s);
		}
	}
	else
	{
		get_input(cmd, s);
		error = execute_cmd(s);
	}
	return (error);
}

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
