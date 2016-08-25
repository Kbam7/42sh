/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 16:02:44 by kbamping          #+#    #+#             */
/*   Updated: 2016/08/24 19:47:12 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int			get_pos(char *str, char ch)
{
	int	pos;

	pos = 0;
	while (str[pos] != '\0')
	{
		if (str[pos] == ch)
			return (pos);
		++pos;
	}
	return (-1);
}

/*
** This function checks if there are chars before or after the redir symbol.
*/
char		*analyze_redir(char **str, char dir, char **cmd, t_shell *s)
{
	int		pos;

	s->redir.dir = dir;
	if (*str == NULL || (pos = get_pos(*str, dir)) == -1)
		return (NULL);
	if (pos > 0)
		*str = check_prefix(str, pos, cmd, s);
	
	if (*str == NULL || (pos = get_pos(*str, dir)) == -1)
		return (NULL);
	if ((*str)[pos + 1] && (*str)[pos + 1] == dir)			// ('>>' || '<<')
		++pos;
	if ((*str)[pos + 1] && (*str)[pos + 1] == '>')			// ('>>>')
		return (err(ERR_BAD_TOKEN, ">") ? NULL : NULL);
	if ((*str)[pos + 1] && (*str)[pos + 1] == '<')			// ('<<<')
		++pos;
	if (*str && (*str)[pos + 1] && (*str)[pos + 1] != '\0')
		*str = check_postfix(str, pos, s);

	if ((*str) == NULL)
		return (NULL);
	return (ft_strdup(*str));
}
