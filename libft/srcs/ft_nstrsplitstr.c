/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nstrsplitstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 23:33:54 by kbamping          #+#    #+#             */
/*   Updated: 2016/09/11 11:58:16 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(const char *str, char *sp)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_strncmp((str + i), sp, ft_strlen(sp)) != 0)
			i++;
		while (ft_strncmp((str + i), sp, ft_strlen(sp)) == 0)
			i += ft_strlen(sp);
		words++;
	}
	return (words);
}

static char		*next_word(const char *str, char *sp, size_t *len)
{
	size_t	i;

	i = 0;
	*len = 0;
	while (str[i] && (ft_strncmp((str + i), sp, ft_strlen(sp)) == 0))
		i += ft_strlen(sp);
	str += i;
	while (str[*len] && (ft_strncmp((str + *len), sp, ft_strlen(sp)) != 0))
		(*len)++;
	return ((char *)(str));
}

t_split_string	ft_nstrsplitstr(char const *str, char *sp)
{
	t_split_string	split;
	size_t			wordl;
	size_t			i;

	i = 0;
	split.words = count_words(str, sp);
	split.strings = (char **)malloc(sizeof(char *) * split.words);
	if (split.strings == NULL)
	{
		split.words = -1;
		return (split);
	}
	while (i < split.words)
	{
		str = next_word(str, sp, &wordl);
		split.strings[i] = (char *)ft_strsub(str, 0, wordl);
		if (split.strings[i] == NULL)
		{
			split.words = -1;
			return (split);
		}
		str += wordl;
		i++;
	}
	return (split);
}
