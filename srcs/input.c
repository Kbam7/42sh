/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/03 13:57:31 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	**trim_commands(char **tab, int len)
{
	int		i;
	char	**trimmed;

	i = 0;
	if (len > 0)
	{
		trimmed = (char **)malloc(sizeof(char *) * len + 1);
		while (i < len)
		{
			trimmed[i] = ft_strtrim(tab[i]);
			ft_strdel(&tab[i]);
			++i;
		}
		trimmed[len] = NULL;
		return (trimmed);
	}
	return (tab);
}

int	process_input(char *cmd, t_shell *s)
{
	int			error;

/*
				if ('|')	// if there is '|' in cmd
//					process_input(cmd_list->cmd, s);
				else if (!'|' && ('<' || '>') ) // if there is '>' or '<' in cmd. there will not be pipes in cmd.
//					execute_redir(cmd_list->redir);
*/			
	error = EXIT_FAILURE;
	if (ft_strchr(cmd, '|'))
	 return (process_pipes(cmd, s));
	else if (ft_strchr(cmd, '<') /*or '>'*/) // there will be no '|' in cmd
		return (error);
	// return (process_redirs(cmd, s));
	else
	{	// try execute cmd
		// cmd string doesnt have any operators (< > |)
		// check if is a file or a cmd

		// if there are still
		// and execute.
		get_input(cmd, s);

printf("Trying to execute '%s' with '%s' ...", s->input[0], s->input[1]); // debug

		error = execute_cmd(s); // exucutes the function and reads output to write_fd
		free_tab((void **)s->input, ft_tablen(s->input));
	}
	return (error);
}

int		process_pipes(char *cmd, t_shell *s)
{
	t_split_string	sub_cmd;
	int				i;

	// split and use split[n - 1] as stdin for split[n] so that each pipe/cmd gets stdin from the pipe/cmd before it.
	sub_cmd = ft_nstrsplit(cmd, '|');
	sub_cmd.strings = trim_commands(sub_cmd.strings, sub_cmd.words);
	s->pipes = (int **)malloc(sizeof(int *) * sub_cmd.words);

	// cycle through split[] and process_input() each argument to check for redirs(< , >) or if can execute.
	while (sub_cmd.strings[s->pipe_i] && (s->n_pipes = sub_cmd.words - s->pipe_i) > 0)
	{
		i = s->pipe_i;
		if (s->n_pipes == 1 && sub_cmd.strings[i] == NULL)
		{
		// user has input "cat author |", there is no command after the pipe so
		//	read one line(ft_gnl), and use that line as a command. This command may be
		//	multiple commands piped together, so running the input through from
		//	the top of the program would be a good idea.
		//	basically, fork, and run shell_loop() again. Make sure to pipe the STDOUT
		//	into the write-end of the pipe (s->pipe_fd[1]). Then this parent which
		//	is the parent of shell_loop, waits for the child and then uses the pipe
		}
		else
		{
			//	For pipes and redirs, make an array of integer arrays with 2 ints in each array.
			s->pipes[i] = (int *)malloc(sizeof(int) * 2);
			if (pipe(s->pipes[i]) == -1)
				return (err(ERR_CREATE_PIPE, "execute_cmd()"));

			// if after first pipe/command, then read from the pipe, else read from STDIN
			s->read_fd = (i > 0) ? s->pipes[i - 1][0] : STDIN_FILENO;
// NOTE!!->	//	to read s->read_fd -- dup2(STDIN_FILENO, s->read_fd);

			// while not last pipe output to pipe[i][1] else output to STDOUT
			s->write_fd = (s->n_pipes > 1) ? s->pipes[i][1] : STDOUT_FILENO;
			//	to write to s->write_fd -- dup2(STDOUT_FILENO, s->write_fd);

	printf("s->write_fd >%d\ts->pipe[i][1] >%d\ns->read_fd >%d\ts->pipe[i - 1][0] >%d\n", s->write_fd, s->pipes[i][1], s->read_fd, s->pipes[i][0]); // debug
			process_input(sub_cmd.strings[i], s);

// At this point, the output has been read into the pipe or to the screen if its the last command.


/* This step is handled by setting write_fd to either STDOUT or pipe[1]
			if (s->n_pipes == 1)//	if on the last cmd being piped to, then write its output to the screen
			{
				ft_putstr_fd("Reading from pipe[0] to  STDOUT_FILENO\n", 2); // debug
				while (read(s->pipe[0], &buf, 1) > 0)
					write(STDOUT_FILENO, &buf, 1);
			}
			else // read output_pipe into input
			{
				ft_putstr_fd("There are still commands to piped\n"
					"-- Read from pipe[0] in next command\n", 2);	// debug
			}
*/

		}
		++s->pipe_i;
	}
/*
	if (s->pipes.n_pipes == 0) // all pipes have been executed, write to stdout.
		while (read(s->pipes.pipe[0], &buf, 1) > 0)// Read from read-end of pipe
			write(s->write_fd, &buf, 1);	// write to screen
*/		
	free_tab((void **)s->pipes, s->pipe_i);
	free_tab((void **)sub_cmd.strings, ft_tablen(sub_cmd.strings));
	return (EXIT_SUCCESS);
}


/*
int		process_redir(char *cmd, t_shell *s)
{
			//	For pipes and redirs, make an array of integer arrays with 2 ints in each array.
			//	redirs = (int **)malloc(sizeof(int *) * sub_cmd.words + 1);

					// split. can separate by space ' '. All redirs will be separated by space, else error.
					// if is a redirect, found out which way it going and execute it with redir_input() or redir_output()

					//	if "<&-" or  ">&-"
					//	if '<', 
					//		split[n] is stdin for split[n - 1].
					// 		set_redirect(); // sets input and output fd.
					//	if '>',
					//		split[n] is stdin for split[n + 1].
					// 		set_redirect(); // sets input and output fd.
}
*/


/*
execute_pipes(t_cmd_list *pipe_list, t_shell *s)
{
		while (pipe_list)
		{
//		printf("shell_loop() - pipe -- get_input(%s)\n", command->cmd); // debug
			get_input(pipe_list, s);

			if (s->input)

//		printf("shell_loop() - pipe -- execute_cmd(%s)\n", s->input[0]); // debug
			ret = execute_cmd(s, command->cmd);
			free_tab((void **)s->input, ft_tablen(s->input));
			if (ret == EXIT_SH)
				break ;
			pipe_list = pipe_list->next;
		}
}

execute_redir(t_cmd_list *redir_list, t_shell *s)
{
		while (redir_list)
		{
			get_input()
//	printf("shell_loop() - pipe -- get_input(%s)\n", command->cmd); // debug
			get_input(command, s);
//	printf("shell_loop() - pipe -- execute_cmd(%s)\n", s->input[0]); // debug
			ret = execute_cmd(s, command->cmd);
			free_tab((void **)s->input, ft_tablen(s->input));
		}
}
*/
