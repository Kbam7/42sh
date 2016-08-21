/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/20 14:08:44 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	reset_and_free_vars(t_shell *s)
{
	free_tab((void ***)&s->redir.rdr, ft_tablen(s->redir.rdr));
	free_tab((void ***)&s->redir.cmd, ft_tablen(s->redir.cmd));
	s->redir.n_rdr = 0;
	s->redir.rdr_i = 0;
}

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
dprintf(2, "----------  process_redir() - execute_redirs() -- Output redir\n"
			"s->redir.cmd[%d] = '%s'\ns->redir.rdr[%d] = '%s'\ns->redir.cmd[%d] = '%s'\n",
											i, s->redir.cmd[i], i, s->redir.rdr[i], i+1, s->redir.cmd[i+1]);// debug

			s->redir.dir = '>';
			// create file here and open it for writing, then execute the process
			ret = process_input(s->redir.cmd[i], s);
		}
		else if (ft_strchr(s->redir.rdr[i], '<'))
		{
dprintf(2, "----------  process_redir() - execute_redirs() -- Input redir\n"
			"s->redir.cmd[%d] = >%s<\ns->redir.rdr[%d] = >%s<\n", i, s->redir.cmd[i], i, s->redir.rdr[i]);	// debug

			s->redir.dir = '<';
			// open file for reading here, then execute cmd.
			ret = process_input(s->redir.cmd[i], s);
		}
		if (ret != EXIT_SUCCESS)
			break ;
		++i;
	}
	reset_and_free_vars(s);
	return (ret);
}

static int	get_redir_string(char **str, char **cmd, int dir, t_shell *s)
{
	char			*rdr_str;
	
	rdr_str = NULL;
	rdr_str = analyze_redir(str, dir, cmd, s);

dprintf(2, "process_redir() - get_redir_string() -- str = '%s' -- "
		"rdr_str == >%s< && cmd == >%s<\n", *str, rdr_str, *cmd); // debug

	if (!rdr_str || add_redir(&rdr_str, cmd, s) == EXIT_FAILURE)
	{
		ft_strdel(&rdr_str);
		return (EXIT_FAILURE);
	}
	ft_strdel(&rdr_str);
	return (EXIT_SUCCESS);
}

int		process_redir(char *str, t_shell *s)
{
	t_split_string	sp;
	char			**tmp;
	char			*cmd;
	char			*oldcmd;
	int				i;

	sp = ft_nstrsplit(str, ' ');
	tmp = sp.strings;
	sp.strings = tab_trim(tmp, (int)sp.words);
	free_tab((void ***)&tmp, sp.words);
	cmd = ft_strnew(1);
	i = 0;
	while (i < (int)sp.words)
	{
		
		if (ft_strchr(sp.strings[i], '>'))
		{
			if (get_redir_string(&sp.strings[i], &cmd, '>', s) == EXIT_FAILURE)		
				return (EXIT_FAILURE);
		}
		else if (ft_strchr(sp.strings[i], '<')) //  MAKE THIS RUN THE SAME CODE AS '>'
		{
			if (get_redir_string(&sp.strings[i], &cmd, '<', s) == EXIT_FAILURE)		
				return (EXIT_FAILURE);
		}
		else
		{
dprintf(2, "process_redir() -- NO REDIR in this string, save to existing cmd -- current cmd = >%s<\n", cmd); // debug
			oldcmd = (cmd == NULL) ? ft_strnew(1) : cmd;
			cmd = ft_strjoinstr(oldcmd, sp.strings[i], " ");
dprintf(1, "process_redir() -- oldcmd = >%s<\tnew cmd = >%s<\n", oldcmd, cmd); // debug
			ft_strdel(&oldcmd);
		}
		if (s->redir.nxt_cmd)
		{
			oldcmd = (cmd == NULL) ? ft_strnew(1) : cmd;
			cmd = ft_strjoinstr(s->redir.nxt_cmd, " ", oldcmd);
			ft_strdel(&oldcmd);
			ft_strdel(&s->redir.nxt_cmd);
		}
		if ((i + 1) == (int)sp.words && cmd) // last word? i.e, no redir after this string ... add cmd to list of cmds
		{
dprintf(2, "process_redir() -- Adding last cmd -- cmd = >%s<\n", cmd);
			if (add_redir(&rdr_str, &cmd, s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		++i;
	}
	free_tab((void ***)&sp.strings, sp.words);

	return (execute_redirs(s));
}
