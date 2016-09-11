/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 12:26:59 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	execute_redirs(t_shell *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = EXIT_SUCCESS;
	while (i < s->redir.n_rdr)
	{
		s->redir.rdr_i = i;
		if (ft_strchr(s->redir.rdr[i], '>'))
		{
			s->redir.dir = '>';
			ret = process_input(s->redir.cmd[i], s);
		}
		else if (ft_strchr(s->redir.rdr[i], '<'))
		{
			s->redir.dir = '<';
			ret = process_input(s->redir.cmd[i], s);
		}
		if (ret != EXIT_SUCCESS)
			break ;
		++i;
	}
	redirs_reset_and_free_vars(s);
	return (ret);
}

static int	get_redir_string(char **str, char **cmd, int dir, t_shell *s)
{
	char			*rdr_str;

	rdr_str = NULL;
	rdr_str = analyze_redir(str, dir, cmd, s);
	if (!rdr_str || add_redir(&rdr_str, cmd, s) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (s->redir.nxt_cmd)
		if (add_redir(&rdr_str, &s->redir.nxt_cmd, s) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	process_redir_check(int i, char **cmd, t_shell *s)
{
	char			*tmp;

	if (ft_strchr(s->redir.sp.strings[i], '>'))
	{
		if (get_redir_string(&s->redir.sp.strings[i], cmd, '>', s)
																== EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strchr(s->redir.sp.strings[i], '<'))
	{
		if (get_redir_string(&s->redir.sp.strings[i], cmd, '<', s)
																== EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		tmp = (*cmd == NULL) ? ft_strnew(1) : *cmd;
		*cmd = ft_strjoinstr(tmp, s->redir.sp.strings[i], " ");
		ft_strdel(&tmp);
	}
	return (EXIT_SUCCESS);
}

int			process_redir(char *str, t_shell *s)
{
	char			*cmd;
	char			*tmp;
	int				i;

	cmd = ft_strnew(1);
	s->redir.sp_i = get_string_words(str, s);
	while (s->redir.sp_i < (int)s->redir.sp.words)
	{
		i = s->redir.sp_i;
		if (process_redir_check(i, &cmd, s) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if ((i + 1) == (int)s->redir.sp.words && cmd)
		{
			tmp = ft_strnew(1);
			if (add_redir(&tmp, &cmd, s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		s->redir.sp_i++;
	}
	free_tab((void ***)&s->redir.sp.strings, s->redir.sp.words);
	return (execute_redirs(s));
}
