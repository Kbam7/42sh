/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:50 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/16 18:01:22 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
syntax error near unexpected token `newline' -- For ERR_BAD_TOKEN
*/

#include "ft_shell.h"

static char	*check_file_error(int errno, char *msg)
{
	if (errno == ERR_MAX_PATHLEN)
		return (ft_strjoinstr("Maximum path length reached.\n'", msg, "'"));
	else if (errno == ERR_CREATE)
		return (ft_strjoinstr("File/Directory cannot be created '", msg, "'"));
	else if (errno == ERR_NO_FILE)
		return (ft_strjoinstr("File/Directory does not exist '", msg, "'"));
	else if (errno == ERR_NO_READ)
		return (ft_strjoinstr("User hasn't got read rights for '", msg, "'"));
	else if (errno == ERR_NO_WRITE)
		return (ft_strjoinstr("User hasn't got write rights for '", msg, "'"));
	else if (errno == ERR_NO_EXEC)
		return (ft_strjoinstr("User hasn't got exec rights for '", msg, "'"));
	else
		return (NULL);
}

static void	check_errno(char **tmp, int errno, char *msg)
{
	if (errno == ERR_INVALID_ARG)
		*tmp = ft_strjoinstr("Invalid arguments for '", msg, "'");
	else if (errno == ERR_MALLOC)
		*tmp = ft_strjoinstr("malloc error in '", msg, "'. That sounds bad. .");
	else if (errno == ERR_BAD_TOKEN)
		*tmp = ft_strjoinstr("syntax error near unexpected token '", msg, "'");
	else if (errno == ERR_CREATE_PIPE)
		*tmp = ft_strjoinstr("pipe() failed in '", msg, "' function.");
	else if (errno == ERR_INVALID_PIPE)
		*tmp = ft_strjoinstr("Invalid pipe '", msg, "'");
	else if (errno == ERR_GNL)
		*tmp = ft_strjoinstr("Oh no!! Its a '", msg, "'. That sounds bad. .");
	else if (errno == ERR_NOTFOUND)
		*tmp = ft_strjoinstr("Command '", msg, "' not found");
	else if (errno == ERR_FORK_FAILED)
		*tmp = ft_strjoinstr("Fork failed! '", msg, "'");
	else if (errno == ERR_CHDIR)
		*tmp = ft_strjoinstr("Cannot change to directory '", msg, "'");
	else if ((*tmp = check_file_error(errno, msg)) != NULL)
		*tmp = *tmp;
	else
		*tmp = NULL;
//		*tmp = ft_strdup("No further details");
}

int			err(int errno, char *msg)
{
	static char	*err = "\033[01;31mError!\033[0m -- ";
	char		*err_msg;
	char		*tmp;

	if (errno == EXIT_SH)
		return (errno);
	check_errno(&tmp, errno, msg);
	if (tmp != NULL)
	{
		err_msg = ft_strjoin(err, tmp);
		ft_putendl_fd(err_msg, STDERR_FILENO);
		free(tmp);
		free(err_msg);
	}
	return (errno);
}
