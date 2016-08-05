/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 08:25:22 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/05 13:53:00 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		process_redir(char *cmd, t_shell *s)
{
	t_split_string	sub_cmd;
	char			**tmp;
	size_t				i;
// Redirection allows commands’ file handles to be duplicated, opened, closed,
// made to refer to different files, and can change the files the command reads from and writes to.

			//	For pipes and redirs, make an array of integer arrays with 2 ints in each array.
			//	redirs = (int **)malloc(sizeof(int *) * sub_cmd.words + 1);

					// split. can separate by space ' '. All redirs will be separated by space, else error.
					// if is a redirect, found out which way it going and execute it with redir_input() or redir_output()

					//	if "<&-" or  ">&-" close STDIN or STDOUT repectively
					//	if '<', 
					//		split[n] is stdin for split[n - 1].
					// 		set_redirect(); // sets input and output fd.
					//	if '>',
					//		split[n] is stdin for split[n + 1].
					// 		set_redirect(); // sets input and output fd.


	if (ft_strchr(cmd, '>'))
	{
		// do OUTPUT REDIR '>'
	sub_cmd = ft_nstrsplit(cmd, '>');
	tmp = trim_commands(sub_cmd.strings, (int)sub_cmd.words);
	free_tab((void **)sub_cmd.strings, sub_cmd.words);
	sub_cmd.strings = ft_tabdup(tmp, sub_cmd.words);

	// loop through sub_cmd.strings[] and execute
	while (sub_cmd.strings[s->redir_i] && (s->n_redirs = sub_cmd.words - s->redir_i) > 0)
	{
		i = s->pipe_i;
		process_input(sub_cmd.strings[i], s);
		++s->pipe_i;
	}



	else if (ft_strchr(cmd, '<'))
	{
		// do INPUT REDIR '<'
	}

	// split and use split[n - 1] as stdin for split[n] so that each pipe/cmd gets stdin from the pipe/cmd before it.
	sub_cmd = ft_nstrsplit(cmd, '<');
	tmp = trim_commands(sub_cmd.strings, (int)sub_cmd.words);
	free_tab((void **)sub_cmd.strings, sub_cmd.words);
	sub_cmd.strings = ft_tabdup(tmp, sub_cmd.words);
	free_tab((void **)tmp, sub_cmd.words);

//dprintf(2, "process_pipe() ---- Here - 1\n"); // debug

	// Create int **array for pipes
	s->pipes = (int **)malloc(sizeof(int *) * sub_cmd.words);
	i = 0;
	while (i < sub_cmd.words)
	{
		s->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(s->pipes[i]) == -1)
			return (err(ERR_CREATE_PIPE, "execute_cmd()"));
		++i;
	}

}
