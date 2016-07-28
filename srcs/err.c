/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 01:25:50 by kbamping          #+#    #+#             */
/*   Updated: 2016/07/27 13:12:32 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	check_errno(char **tmp, int errno, char *msg)
{
	if (errno == ERR_INVALID_ARG)
		*tmp = ft_nstrjoin("Invalid arguments for '", msg, "'");
	else if (errno == ERR_NOTFOUND)
		*tmp = ft_nstrjoin("Command '", msg, "' not found");
	else if (errno == ERR_CHDIR)
		*tmp = ft_nstrjoin("Cannot change to directory '", msg, "'");
	else if (errno == ERR_MAX_PATHLEN)
		*tmp = ft_nstrjoin("Maximum path length reached.\n'", msg, "'");
	else if (errno == ERR_NO_FILE)
		*tmp = ft_nstrjoin("File/Directory does not exist '", msg, "'");
	else if (errno == ERR_NO_READ)
		*tmp = ft_nstrjoin("User does not have read rights for '", msg, "'");
	else if (errno == ERR_NO_WRITE)
		*tmp = ft_nstrjoin("User does not have write rights for '", msg, "'");
	else if (errno == ERR_NO_EXEC)
		*tmp = ft_nstrjoin("User does not have execute rights for '", msg, "'");
	else
		*tmp = ft_strdup("No further details");
}

int			err(int errno, char *msg)
{
	static char	*err = "\033[01;31mError!\033[0m -- ";
	char		*err_msg;
	char		*tmp;

	check_errno(&tmp, errno, msg);
	err_msg = ft_strjoin(err, tmp);
	ft_putendl(err_msg);
	free(tmp);
	free(err_msg);
	return (errno);
}
