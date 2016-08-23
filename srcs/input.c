/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/22 23:55:42 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	process_input(char *cmd, t_shell *s)
{
	int			error;

	error = EXIT_FAILURE;
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
