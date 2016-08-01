/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/01 23:23:04 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"


int	check_builtin_env_funcs(t_shell *s)
{
	if (ft_strcmp(s->input[0], "env") == 0)
		return (ft_env(s->input, s));
	else if (ft_strcmp(s->input[0], "set") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "setenv") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "export") == 0)
		return (ft_set(1, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "unsetenv") == 0)
		return (ft_unsetenv(s->input[1], s));
	else if (ft_strcmp(s->input[0], "unset") == 0)
		return (ft_unsetenv(s->input[1], s));
	else
		return (ERR_NOTFOUND);
}

/*
int	check_assign_variable(t_shell *s)
{
	int	i;

	i  0;
	while (s->input[i])
		if (ft_strchr(s->input[i], '='))
	else
		return (ERR_NOTFOUND);
}
*/

int	try_builtin(t_shell *s)
{
	int	ret;

	if (ft_strcmp(s->input[0], "cd") == 0)
		return (ft_cd(s->input, s));
	else if (ft_strcmp(s->input[0], "echo") == 0)
		return (ft_echo(s->input, s));
	else if (ft_strcmp(s->input[0], "21sh") == 0)
		return (run_shell(s));
	else if ((ret = check_builtin_env_funcs(s)) != ERR_NOTFOUND)
		return (ret);
//	else if ((ret = check_assign_variable(s)) != ERR_NOTFOUND)
//		return (ret);
	else
		return (ft_strcmp(s->input[0], "exit") == 0 ? EXIT_SH : ERR_NOTFOUND);
}

int		try_system(t_shell *s)
{
	int		i;
	char	*path;
	char	**var;

	i = 0;
	var = (ft_strcmp(s->input[0], "printenv") == 0) ?
													s->env_var : s->shell_var;
	while (s->paths[i] != NULL)
	{
		path = ft_strjoinstr(s->paths[i], "/", s->input[0]);
		if (access(path, F_OK) == 0)
			if (check_rights(path, 'r', 0, 'x') == EXIT_SUCCESS)
			{
				if (execve(path, s->input, var) != -1)
					ft_strdel(&path);
				exit(EXIT_SUCCESS);
			}
		ft_strdel(&path);
		++i;
	}
	free_tab(s->input, ft_tablen(s->input));
	free_t_shell(s);
	exit(EXIT_FAILURE);
}

int		execute_cmd(t_shell *s)
{
	pid_t	pid;
	int		status;

	status = EXIT_FAILURE;
	if ((status = try_builtin(s)) == ERR_NOTFOUND)
	{

//	output_fd will be stdout(1) as default. 

//	If a left redir(<) is found, read from arg defined after (<). i.e execute arg, and read its output into cmd. e.g	cmd < file.txt
//																														open file.txt
//																														read file.txt into stdin for cmd.

//	If a fd is given in the command,
//		then output_fd will be set to the one defined	

//	execute_cmd must get a output_fd as a param, or store one in the t_shell s.
//	child process reads from stdin and must write to the output_fd given.

//	the parent process will read from the child. (pipe_fd[0] = 0(stdin), pipe_fd[1] = output_fd))
//	the parent process will wait for the child
		pid = fork();
		if (pid < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
			try_system(s);
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == EXIT_FAILURE)
			err(ERR_NOTFOUND, s->input[0]);
	}
	return (status);
}
