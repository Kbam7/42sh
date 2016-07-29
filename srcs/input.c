/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/30 00:05:51 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	save_input(char *line, t_shell *s)
{
	char			*tmp;
	t_split_string	data;

	tmp = ft_strtrim(line);
	data = ft_nstrsplit(tmp, ' ');
	ft_strdel(&line);
	ft_strdel(&tmp);
	s->input = ft_tabdup(data.strings, data.words);
	free_tab(data.strings, data.words);
}

static int	process_input(char *line, t_shell *s)
{
	t_split_string	commands;
	int				i;
	int				error;

//	Once the first input from ft_gnl is read, the s->commands list will have one
//	node. From there, we can test that node to see how deep we can break it down
//	into sub-commands.

	i = 0;
	while (s->commands != NULL)
	{
		if (ft_strchr(line, '|'))
			error = check_pipe(line, s);
		else if (ft_strchr(line, '<') || ft_strchr(line, '>'))
			error = check_redirect(line, s);
	//	else if special
		if (error)
			// print error
	}
	if (s->commands == NULL)
	{
		if ((ret = add_cmd_list(&s->commands, str)) == EXIT_FAILURE)
			return (ERR_);
			ret = check_pipe(&s->command, s);
	}
	}
	return (process_input(line, s));
}

int		get_input(t_shell *s)
{
	char			*line;
	int				ret;
	char			*tmp;

	if ((ret = ft_gnl(0, &tmp)) > 0)
	{
		line = ft_strtrim(tmp);
		ft_strdel(tmp);
		process_input(line, s);
//		save_input(line, s);
	}
	if (ret < 0)
		ft_putstr_fd("ft_gnl Error!\n", 2);
	return (ret);
}
