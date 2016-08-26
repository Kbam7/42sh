/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:24 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/26 11:08:26 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static int	check_builtin_env_funcs(t_shell *s)
{
	char	*tmp;
	int		ret;

	if (ft_strcmp(s->input[0], "env") == 0)
		return (ft_env(s->input, s));
	else if (ft_strcmp(s->input[0], "set") == 0)
		return (ft_set(2, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "setenv") == 0)
		return (ft_set(1, s->input[1], s->input[2], s));
	else if (ft_strcmp(s->input[0], "export") == 0)
	{
		tmp = ft_strdup(ft_getenv(s->input[1], s));
		ret = ft_set(1, s->input[1], tmp, s);
		ft_strdel(&tmp);
		return (ret);
	}
	else if (ft_strcmp(s->input[0], "unsetenv") == 0)
		return (ft_unsetenv(s->input[1], s));
	else if (ft_strcmp(s->input[0], "unset") == 0)
		return (ft_unsetenv(s->input[1], s));
	else
		return (ERR_NOTFOUND);
}

static int	try_parent_builtin(t_shell *s)
{
	if (ft_strcmp(s->input[0], "cd") == 0)
		return (ft_cd(s->input, s));
	else if (ft_strcmp(s->input[0], "exit") == 0)
		return (EXIT_SH);
	else
		return (ERR_NOTFOUND);
}

void    ft_path(t_shell *shell)
{
	char    **line;
	char    **line2;
	int     i;

	line2 = NULL;
	line = NULL;
	i = 0;
	while (shell->env_var[i])
	{
		if (ft_strncmp(shell->env_var[i], "PATH=", 5) == 0)
		{
			line2 = ft_strsplit(shell->env_var[i], '=');
			line = ft_strsplit(line2[1], ':');
			break ;
		}
		i++;
	}
	shell->path = ft_strdup_2(line);
	if (line2 != NULL)
	{
		ft_free_2(line2);
		ft_free_2(line);
		free(line2);
		free(line);
	}
}

int     ft_check_exec(char *path, char **args, t_shell *shell)
{
	char    *file;
	char    *temp;

	temp = ft_strjoin(path, "/");
	file = ft_strjoin(temp, args[0]);
	if (access(file, X_OK) != -1)
	{
		if (execve(file, args, shell->env_var) != -1)
			return (1);
	}
	else if (access(args[0], X_OK) != -1)
		if (execve(args[0], args, shell->env_var) != -1)
			return (1);
	free(file);
	free(temp);
	return (0);
}

int     ft_launch(char **args, t_shell *shell)
{
	pid_t   pid;
	int     status;
	int     i;

	ft_path(shell);
	pid = fork();
	i = -1;
	if (pid == 0)
	{
		while (shell->path[++i])
			if (ft_check_exec(shell->path[i], args, shell) == 1)
				exit(EXIT_SUCCESS) ;
		return(ERR_NOTFOUND);
	}
	else
	{
		wait(&status);
		if (WEXITSTATUS(status) == 0)
			return (EXIT_SUCCESS);
	}

	return (ERR_NOTFOUND);
}

static int  try_child_builtin(t_shell *s)
{
	int ret;

	ret = 1;
	if (ft_strcmp(s->input[0], "echo") == 0)
		return (ft_echo(s->input, s));
	else if ((ret = check_builtin_env_funcs(s)) != ERR_NOTFOUND)
		return (ret);
	else if ((ret = ft_launch(s->input, s)) != ERR_NOTFOUND)
		return (ret);
	return (ERR_NOTFOUND);
}


int	execute_cmd(t_shell *s)
{
	pid_t	pid;
	int		status;
	int		i;

	status = EXIT_FAILURE;
	if ((status = try_parent_builtin(s)) == ERR_NOTFOUND)
	{
		if ((pid = fork()) < 0)
			return (err(ERR_FORK_FAILED, ""));
		if (pid == 0)
		{
			if (s->pipe.n_pipes)
				child_pipe(s);
			if (s->redir.n_rdr)
			{
				i = s->redir.rdr_i;
				if (s->redir.dir == '>')
					child_output_redir(s->redir.rdr[i], s);
				else if (s->redir.dir == '<')
					child_input_redir(s->redir.rdr[i], s);
			}
			if ((try_child_builtin(s)) == EXIT_SUCCESS)
				status = EXIT_SUCCESS;
			exit(status == 0 ? 0 : (status - 900));
		}
		// -----   Parent only   ------
		if (s->pipe.n_pipes)// if no redirs, then do pipes if there are any..
			parent_pipe(s);
		//	wait for child to finish
		wait(&status);
		// error checks
		if (WIFEXITED(status) && (status = WEXITSTATUS(status)) != EXIT_SUCCESS)
			return (err(((status == 1) ? 1 : status + 900), s->input[0]));
	}
	write(1, "$> ", 2);
	return (status);
}

