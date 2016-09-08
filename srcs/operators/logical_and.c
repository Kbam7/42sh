/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 01:24:50 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/06 17:18:33 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	init_logical_and(char *cmd, char ***cmds)
{
	t_split_string	split;
	char			**tmp;

	split = ft_nstrsplitstr(cmd, "&&");
	tmp = tab_trim(split.strings, (int)split.words);
	free_tab((void ***)&split.strings, split.words);
	*cmds = ft_tabdup(tmp, split.words);
	free_tab((void ***)&tmp, split.words);
}

int			process_logical_and(char *cmd, t_shell *s)
{
	char	**cmds;
	int		ret;
	int		i;

	i = 0;
	init_logical_and(cmd, &cmds);
	while (cmds[i] != NULL)
	{
dprintf(2, "process_logical_and() -- process_input('%s')\n", cmds[i]); // debug
		if ((ret = process_input(cmds[i], s)) != EXIT_SUCCESS)
			break ;
		++i;
	}
	free_tab((void ***)&cmds, ft_tablen(cmds));
	return (ret);
}
