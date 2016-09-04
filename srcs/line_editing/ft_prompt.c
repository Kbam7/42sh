/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/04 09:14:43 by kgani             #+#    #+#             */
/*   Updated: 2016/09/04 09:18:28 by kgani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void ft_prompt_print(t_shell *s)
{
	ft_putstr(s->prompt);
}

void ft_prompt_new(char *new_prompt, t_shell *s)
{
	if (s->prompt)
		free (s->prompt);
	s->prompt = ft_strdup(new_prompt);
	s->prompt_len = ft_strlen(new_prompt);
}

