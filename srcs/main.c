/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 20:35:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 18:04:33 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int			main(int argc, char **argv, char **envp)
{
	t_shell	*s;

	ft_signals();
	s = ft_get_shell();
	init_env(s, argc, argv, envp);
	init_terminal_data(s);
	ft_clear_screen();
	set_prompt(s);
	ft_putstr(s->prompt);
	shell_loop(s);
	free_t_shell(s);
	return (EXIT_SUCCESS);
}
