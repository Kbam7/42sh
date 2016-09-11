/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 12:10:59 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 12:18:51 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	redirs_reset_and_free_vars(t_shell *s)
{
	free_tab((void ***)&s->redir.rdr, ft_tablen(s->redir.rdr));
	free_tab((void ***)&s->redir.cmd, ft_tablen(s->redir.cmd));
	s->redir.n_rdr = 0;
	s->redir.rdr_i = 0;
}

int		get_string_words(char *str, t_shell *s)
{
	char			**tmp;

	s->redir.sp = ft_nstrsplit(str, ' ');
	tmp = s->redir.sp.strings;
	s->redir.sp.strings = tab_trim(tmp, (int)s->redir.sp.words);
	free_tab((void ***)&tmp, s->redir.sp.words);
	return (0);
}
