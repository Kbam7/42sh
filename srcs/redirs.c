/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/12 00:22:27 by kbamping         ###   ########.fr       */
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
dprintf(2, "----------  process_redir() - execute_redirs()\n"
			"s->redir.cmd[%d] = >%s<\ns->redir.rdr[%d] = >%s<\n", i, s->redir.cmd[i], i, s->redir.rdr[i]);	// debug
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

	int				len;
	int				offset;

	t_split_string	sp;
	char			*tmp;
	char			*cmd;
	char			*oldcmd;
	char			*rdr_str;
	int				i;

	sp = ft_nstrsplit(str, ' ');
	tmp = tab_trim(sp.strings, (int)sp.words);
	free_tab((void **)sp.strings, sp.words);
	sp.strings = ft_tabdup(tmp, sp.words);

	cmd = NULL;
	rdr_str = NULL;

	while (i < sp.words)
	{
		if (ft_strchr(sp.strings[i], '>'))
		{
			// check chars before and after redir, and set appropriate varibles
			rdr_string = analyze_redir(sp.strings[i], '>', &cmd, s);
			if (add_redir(rdr_str, cmd, s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (cmd)
				ft_strdel(&cmd);
			ft_strdel(&rdr_str);
		}
		else if (ft_strchr(sp.strings[i], '<'))
		{ //  MAKE THIS RUN THE SAME CODE AS '>'
		/*
			rdr_str = ft_strdup(s.strings[i]);
			// check chars before and after redir, and set appropriate varibles
			analyze_redir(rdr_str, '<', s);
			if (add_redir(rdr_str, cmd, s) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (cmd)
				ft_strdel(&cmd);
			ft_strdel(&rdr_str);
		*/
		}
		else
		{
			// no redir, so concatinate it to the current cmd
			// join all strings before the current one.

			oldcmd = cmd;
			cmd = ft_strjoinstr(oldcmd, sp.string[j], " ");
			ft_strdel(&oldcmd);

			if ((i + 1) == sp.words) // last word? .. add cmd to list of cmds
				if (add_redir(rdr_str, cmd, s) == EXIT_FAILURE)
					return (EXIT_FAILURE);

		}
		++i;
	}

/*
	i = 0;

	while (cmd[i] != '\0')
	{
		cmd = NULL;
		rdr_str = NULL;
		offset = i;

		//	if write to file
		if (cmd[i] == '>')
		{
		// write output to pipe then write pipe to file/cmd
		// get redir string, and process_output_redir()
			// go to start index of rdr_string
			while (i > 0 && !ft_iswhtspc(cmd[i - 1]))
			{
				--i;
				if (cmd[i] == '&' && cmd[i + 1] == '>')
					break ;

			}

dprintf(1, "process_redir() -- i = %d\toffset = %d --\n", i, offset); // debug

			if (i > offset)	// if i > offset, then the loop above executed atleast once
							//	and there are chars before rdr_string
			{
			//	save as a command to execute.
		 		cmd = ft_strsub(cmd, offset, (i - offset));
			}

dprintf(1, "process_redir() -- before check_prefix() --  cmd -- '%s' --\n", cmd); // debug

			len = i; // i == start index of redir_str
			// check if chars before redir are an integer, if they are then set it to s->redir.out_fd
			check_prefix(cmd, i, '>', s);

			// go to end of rdr_string. (white-space or EOL)
			while (cmd[len] != '\0' && !ft_iswhtspc(cmd[len]))
				++len;
			//	save rdr_string
			rdr_str = ft_strsub(cmd, i, len - 1);

			if (add_redir(rdr_str, cmd, s) == EXIT_FAILURE)
				return (err(ERR_MALLOC, "add_redir() --"));

			i = len;

dprintf(1, "process_redir() --\nadded rdr_str and cmd\n'%s' -- '%s'\n", rdr_str, cmd); // debug
//dprintf(1, "process_redir()\n", tmp); // debug

		}
		else if (cmd[i] == '<')
		{
			// get stdin from cmd after '<'..

		}
		else
			++i;
	}

	// check to see if i > len. If they are equal, it means we ended on a redir. and all has been stored ( _ > )
	// if 'i' is greater, it means cmd ends with a cmd string and we must save the leftover ( __ > __ )
	if (i > len)
	{
		// save remaining chars i --> length
		cmd = ft_strsub(cmd, i, (ft_strlen(cmd) - i));
		if (add_redir(NULL, cmd, s) == EXIT_FAILURE)
			return (err(ERR_MALLOC, "add_redir()"));
	}
*/
	return (execute_redirs(s));
}
