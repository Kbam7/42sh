/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/22 09:59:02 by kbamping         ###   ########.fr       */
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

	if (!rdr_str || add_redir(&rdr_str, cmd, s) != EXIT_SUCCESS) // cmd must == '-' IF ('>-' || '<-')
		return (EXIT_FAILURE);
	if (s->redir.nxt_cmd) // save as next cmd, the rest of the strings must go to cmd[i] i.e. the cmd, no the path. The path is from nxt_cmd at this point
	{
		if (add_redir(&rdr_str, &s->redir.nxt_cmd, s) != EXIT_SUCCESS)
			return (EXIT_FAILURE);

	//	nxt_cmd will now be at cmd[i + 1]
	//	make a function that will cycle through the remaining strings and add any other non-redir strings to cmd[i]
	//	and add any redir strings to s->redir.rdr


/*		oldcmd = (cmd == NULL) ? ft_strnew(1) : cmd;
		cmd = ft_strjoinstr(s->redir.nxt_cmd, " ", oldcmd);
		ft_strdel(&oldcmd);
		ft_strdel(&s->redir.nxt_cmd);
*/	}

	return (EXIT_SUCCESS);
}

static int	get_string_words(char *str, t_shell *s)
{
	char			**tmp;

	s->redir.sp = ft_nstrsplit(str, ' ');
	tmp = s->redir.sp.strings;
	s->redir.sp.strings = tab_trim(tmp, (int)s->redir.sp.words);
	free_tab((void ***)&tmp, s->redir.sp.words);
	return (0);
}

int		process_redir(char *str, t_shell *s)
{
	char			*cmd;
	char			*oldcmd;
	int				i;

	cmd = ft_strnew(1);
	s->redir.sp_i = get_string_words(str, s);
	while (s->redir.sp_i < (int)s->redir.sp.words)
	{
		i = s->redir.sp_i;
		if (ft_strchr(s->redir.sp.strings[i], '>'))
		{
			if (get_redir_string(&s->redir.sp.strings[i], &cmd, '>', s) == EXIT_FAILURE)		
				return (EXIT_FAILURE);
		}
		else if (ft_strchr(s->redir.sp.strings[i], '<')) //  MAKE THIS RUN THE SAME CODE AS '>'
		{
			if (get_redir_string(&s->redir.sp.strings[i], &cmd, '<', s) == EXIT_FAILURE)		
				return (EXIT_FAILURE);
		}
		else
		{
dprintf(2, "process_redir() -- NO REDIR in this string, save to existing cmd -- current cmd = >%s<\n", cmd); // debug
			oldcmd = (cmd == NULL) ? ft_strnew(1) : cmd;
			cmd = ft_strjoinstr(oldcmd, s->redir.sp.strings[i], " ");
dprintf(1, "process_redir() -- oldcmd = >%s<\tnew cmd = >%s<\n", oldcmd, cmd); // debug
			ft_strdel(&oldcmd);
		}
/*		if (s->redir.nxt_cmd)
		{
		// save as cmd[i], and make current
			oldcmd = (cmd == NULL) ? ft_strnew(1) : cmd;
			cmd = ft_strjoinstr(s->redir.nxt_cmd, " ", oldcmd);
			ft_strdel(&oldcmd);
			ft_strdel(&s->redir.nxt_cmd);
		}
*/		if ((i + 1) == (int)s->redir.sp.words && cmd) // last word? i.e, no redir after this string ... add cmd to list of cmds
		{
dprintf(2, "process_redir() -- Adding last cmd -- cmd = >%s<\n", cmd);
			if (add_redir(NULL, &cmd, s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}

		s->redir.sp_i++;


	}
	free_tab((void ***)&s->redir.sp.strings, s->redir.sp.words);

	return (execute_redirs(s));
}
