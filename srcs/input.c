/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/19 12:59:24 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	process_input(char *cmd, t_shell *s)
{
	int			error;

dprintf(2, "----------  process_input() -- START\n");	// debug
	error = EXIT_FAILURE;
	if (ft_strchr(cmd, '|'))
	{
	dprintf(2, "----------  Its a pipe\n");	// debug
		return (process_pipes(cmd, s));
	}
	else if (ft_strchr(cmd, '<') || ft_strchr(cmd, '>'))
	{	// try execute cmd
	dprintf(2, "----------  Its a redir\n");	// debug
		return (process_redir(cmd, s));
	}
	else
	{	// try execute cmd
	dprintf(2, "----------  executing\n");	// debug
		get_input(cmd, s);
		error = execute_cmd(s); // exucutes the function
		free_tab((void ***)&s->input, ft_tablen(s->input));
	}
dprintf(2, "----------  process_input() -- END\n");	// debug
	return (error);
}
