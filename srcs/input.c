/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/28 18:04:04 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		get_input(t_shell *s)
{
	char			*line;
	char			*tmp;
	t_split_string	data;
	int				ret;

	if ((ret = ft_gnl(0, &line)) > 0)
	{
		tmp = ft_strtrim(line);
// split the input by either '|' or ';' and add each command to a command list (linked list).
// check each command to see if there are redirects.
		data = ft_nstrsplit(tmp, ' ');
		ft_strdel(&line);
		ft_strdel(&tmp);
		s->input = ft_tabdup(data.strings, data.words);
		free_tab(data.strings, data.words);
	}
	if (ret < 0)
		ft_putstr_fd("ft_gnl Error!\n", 2);
	return (ret);
}
