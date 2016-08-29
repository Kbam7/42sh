/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/28 16:14:44 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	process_input(char *cmd, t_shell *s)
{
	int			error;

	error = EXIT_FAILURE;
/* // '&&' '||'

--	Add a hook into process_input() for '||' and '&&'..

--	If theres a '||', spilt by '||' and run the first item through process_input()
	and only if it DOES NOT RETURN SUCCESSFULLY will you pass the next item to process_input().

--	If theres a '&&', spilt by '&&' and run the first item through process_input()
	and only if it RETURNS SUCCESSFULLY will you pass the next item to process_input().


*/


	if (ft_strchr(cmd, '|'))
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
