/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/07 14:01:05 by kbamping         ###   ########.fr       */
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
	{	// try execute cmd
		get_input(cmd, s);
		error = execute_cmd(s); // exucutes the function
		free_tab((void **)s->input, ft_tablen(s->input));
	}
	return (error);
}
