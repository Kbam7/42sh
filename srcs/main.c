/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 20:35:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/07 02:03:34 by kbamping         ###   ########.fr       */
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
	ft_prompt_print(s);
	shell_loop(s);
	free_t_shell(s);
	return (EXIT_SUCCESS);
}
