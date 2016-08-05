/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/05 08:25:26 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int	process_input(char *cmd, t_shell *s)
{
	int			error;

	error = EXIT_FAILURE;
	if (ft_strchr(cmd, '|'))
	 return (process_pipes(cmd, s));
	else if (ft_strchr(cmd, '<') /*or '>'*/) // there will be no '|' in cmd
		return (error);
	// return (process_redirs(cmd, s));
	else
	{	// try execute cmd
		get_input(cmd, s);
//dprintf(2, "\n\nprocess_input() -- NEW COMMAND --  calling execute_cmd() input[0] '%s' -- input[1] '%s' ...\n", s->input[0], s->input[1]); // debug

		error = execute_cmd(s); // exucutes the function and reads output to write_fd
		free_tab((void **)s->input, ft_tablen(s->input));
	}
	return (error);
}













