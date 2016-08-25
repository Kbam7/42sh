/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 20:35:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/25 09:26:42 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int			main(int argc, char **argv, char **envp)
{
	t_shell	s;

	init_env(&s, argc, argv, envp);
	init_terminal_data(&s, envp);
	ft_clear_screen();
//	write(1, "$> ", 2);
	shell_loop(&s);
	free_t_shell(&s);
	return (EXIT_SUCCESS);
}
