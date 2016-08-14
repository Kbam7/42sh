/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/14 16:07:35 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	reset_and_free_vars(t_shell *s)
{
	free_tab((void **)s->redir.rdr, ft_tablen(s->redir.rdr));
	free_tab((void **)s->redir.cmd, ft_tablen(s->redir.cmd));
	s->redir.n_rdr = 0;
	s->redir.rdr_i = 0;
}

static int	execute_redirs(t_shell *s)
{
	int	i;
	int	ret;

	i = 0;
	while (i < s->redir.n_rdr)
	{
		s->redir.rdr_i = i;
		if (ft_strchr(s->redir.rdr[i], '>'))
		{
dprintf(2, "----------  process_redir() - execute_redirs() -- Output redir\n"
			"s->redir.cmd[%d] = >%s<\ns->redir.rdr[%d] = '%s'\ns->redir.cmd[%d] = >%s<\n",
											i, s->redir.cmd[i], i, s->redir.rdr[i], i+1, s->redir.cmd[i+1]);// debug
			s->redir.dir = '>';
			ret = process_input(s->redir.cmd[i], s);
		}
		else if (ft_strchr(s->redir.rdr[i], '<'))
		{
//dprintf(2, "----------  process_redir() - execute_redirs() -- Input redir\n"
//			"s->redir.cmd[%d] = >%s<\ns->redir.rdr[%d] = >%s<\n", i, s->redir.cmd[i], i, s->redir.rdr[i]);	// debug
			s->redir.dir = '<';
			ret = process_input(s->redir.cmd[i], s);
		}
		if (ret != EXIT_SUCCESS)
			break ;
		++i;
	}
	reset_and_free_vars(s);
	return (ret);
}

int		process_redir(char *str, t_shell *s)
{
	// the purpose of this loop is to store the redir string and the commands/cmds
	// on either side of the redir. The function then execute the redirs, so it will
	// run until it 


		// split by spaces, check for the split.string with a redir and save it.
		//	all the strings before the string are a command.
		//	search for the next redir,
		//	if no redir, save all the strings after the last redir as
		//	a path to a file. 

	t_split_string	sp;
	char			**tmp;
	char			*cmd;
	char			*oldcmd;
	char			*rdr_str;
	int				i;

	sp = ft_nstrsplit(str, ' ');
	tmp = tab_trim(sp.strings, (int)sp.words);
	free_tab((void **)sp.strings, sp.words);
	sp.strings = ft_tabdup(tmp, sp.words);

	cmd = ft_strnew(1);
	rdr_str = NULL;
	i = 0;
	while (i < (int)sp.words)
	{

dprintf(1, "process_redir() -- after split by ' ' -- sp.strings[%d] = >%s< -- "
		"rdr_str == >%s< && cmd == >%s<\n", i, sp.strings[i], rdr_str, cmd); // debug

//		if (cmd == NULL)
//			cmd = ft_strnew(1);
		if (ft_strchr(sp.strings[i], '>'))
		{
			// check chars before and after redir, and return only the redir string.
			rdr_str = analyze_redir(sp.strings[i], '>', &cmd, s);
			if (!rdr_str || add_redir(&rdr_str, &cmd, s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ft_strchr(sp.strings[i], '<'))
		{
		//  MAKE THIS RUN THE SAME CODE AS '>'
		}
		else
		{
			// no redir, so concatinate it to the current cmd
			// join all strings before the current one.

dprintf(1, "process_redir() -- NO REDIR in this string, save to existing cmd -- current cmd = >%s<\n", cmd); // debug

			oldcmd = (cmd == NULL) ? ft_strnew(1) : cmd;
			cmd = ft_strjoinstr(oldcmd, sp.strings[i], " ");

//dprintf(1, "process_redir() -- oldcmd = >%s<\tnew cmd = >%s<\n", oldcmd, cmd); // debug

			ft_strdel(&oldcmd);
			if (s->redir.nxt_cmd)
			{
				oldcmd = cmd;
				cmd = ft_strjoinstr(s->redir.nxt_cmd, " ", oldcmd);
				ft_strdel(&oldcmd);
				ft_strdel(&s->redir.nxt_cmd);
			}
			if ((i + 1) == (int)sp.words) // last word? i.e, no redir after this string ... add cmd to list of cmds
			{
dprintf(1, "process_redir() -- Adding last cmd -- rdr_str = >%s<\tcmd = >%s<\n", rdr_str, cmd);
				if (add_redir(&rdr_str, &cmd, s) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}

		}
		++i;
	}

	return (execute_redirs(s));
}
