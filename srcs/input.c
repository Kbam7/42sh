/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/06 21:15:12 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	process_input(char *cmd, t_shell *s)
{
	int		error;
	char 	*ret;

	error = EXIT_FAILURE;

dprintf(2, "process_input() -- cmd = '%s'\n", cmd); // debug
	if ((ret = ft_strstr(cmd, "||")))
	{
dprintf(2, "process_input() -- found OR\n"); // debug
		return (process_logical_or(cmd, s));
	}
dprintf(2, "process_input() -- ret from OR check -- ret = '%s'\n", ret); // debug
	if ((ret = ft_strstr(cmd, "&&")))
	{
dprintf(2, "process_input() -- found AND\n"); // debug
		return (process_logical_and(cmd, s));
	}
	else if (ft_strchr(cmd, '|'))
		return (process_pipes(cmd, s));
	else if (ft_strchr(cmd, '<') || ft_strchr(cmd, '>'))
		return (process_redir(cmd, s));
	else
	{
		get_input(cmd, s);
		error = execute_cmd(s);
		free_tab((void ***)&s->input, ft_tablen(s->input));
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
