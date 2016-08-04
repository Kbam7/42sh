/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:03:53 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/04 17:42:09 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static char	**trim_commands(char **tab, int len)
{
	int		i;
	char	**trimmed;

/* START DEBUG */
dprintf(2, "trim_commands() -- len = %d\n", len);	// debug
int	j = 0;
while (j < len)
{
	dprintf(2, "----- pre-trimmed tab[%d] >%s<\n", j, tab[j]);
	++j;
}
/* END DEBUG */

	i = 0;
	if (len > 0)
	{
		trimmed = (char **)malloc(sizeof(char *) * len + 1);
		while (i < len)
		{
			trimmed[i] = ft_strtrim(tab[i]);
			++i;
		}
/* START DEBUG */
int	j = 0;
while (j < len)
{
	dprintf(2, "----- trimmed[%d] >%s<\n", j, trimmed[j]);
	++j;
}
/* END DEBUG */
//		trimmed[len] = NULL;
/* START DEBUG */
j = 0;
dprintf(2, "--- After trimmed[len] assigned to NULL\n");
while (j < len)
{
	dprintf(2, "----- trimmed[%d] >%s<\n", j, trimmed[j]);
	++j;
}
/* END DEBUG */
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
		get_input(cmd, s);
dprintf(2, "process_input() calling execute_cmd() input[0] '%s' -- input[1] '%s' ...\n", s->input[0], s->input[1]); // debug

		error = execute_cmd(s); // exucutes the function and reads output to write_fd
		free_tab((void **)s->input, ft_tablen(s->input));
	}
	return (error);
}

int		process_pipes(char *cmd, t_shell *s)
{
	t_split_string	sub_cmd;
	char			**tmp;
	size_t				i;

	// split and use split[n - 1] as stdin for split[n] so that each pipe/cmd gets stdin from the pipe/cmd before it.
	sub_cmd = ft_nstrsplit(cmd, '|');
	tmp = trim_commands(sub_cmd.strings, (int)sub_cmd.words);
	free_tab((void **)sub_cmd.strings, sub_cmd.words);
	sub_cmd.strings = ft_tabdup(tmp, sub_cmd.words);
	free_tab((void **)tmp, sub_cmd.words);

	// Create int **array for pipes
	s->pipes = (int **)malloc(sizeof(int *) * sub_cmd.words);
	i = 0;
	while (i < sub_cmd.words)
	{
		s->pipes[i] = (int *)malloc(sizeof(int) * 2);
		s->pipes[i][0] = dup(STDIN_FILENO);
		s->pipes[i][1] = dup(STDOUT_FILENO);
		++i;
	}

	// lop through sub_cmd.strings[] and execute
	while (sub_cmd.strings[s->pipe_i] && (s->n_pipes = sub_cmd.words - s->pipe_i) > 0)
	{
		i = s->pipe_i;


		if (pipe(s->pipes[i]) == -1)
			return (err(ERR_CREATE_PIPE, "execute_cmd()"));

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
			process_input(sub_cmd.strings[i], s);
		}
// At this point, the output has been read into the pipe or to the screen if its the last command.
		++s->pipe_i;
	}
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
