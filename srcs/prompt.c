/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:11 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 20:37:25 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

/*
void	intro_message()
{
	static int	flag = 0; // theoretically stops this displaying when launching the shell within itself.

	if (!flag)
	{
//	Have this read in from a file.
	Welcome to my version of Bash. If you would like to have you user name and/or
	current directory displayed, you will need to relaunch with the relevant options.
	[- OPTIONS -]
	-p	Displays current working directory.
	-u	Displays your username
	-pu	Displays both the path and your username

	flag = 1;
	}
}
*/
void	set_prompt(t_shell *s)
{
	char		*tmp;
	static	int	count = 1;

	if (s->prompt && (count == 1 || s->arg_p))
	{
		free(s->prompt);
		if (s->arg_p && s->arg_u)
		{
			tmp = ft_strjoin(":", s->cwd);
			s->prompt = ft_strjoin(ft_getenv("USER", s), tmp);
			ft_strdel(&tmp);
		}
		else if (s->arg_p)
			s->prompt = ft_strjoin(s->cwd, " ");
		else if (s->arg_u)
			s->prompt = ft_strjoin(ft_getenv("USER", s), " ");
		else
			s->prompt = ft_strnew(1);
		tmp = ft_strjoin(s->prompt, "$> ");
		free(s->prompt);
		s->prompt = tmp;
	}
	++count;
}
