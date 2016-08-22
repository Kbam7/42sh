/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 10:35:28 by tmack             #+#    #+#             */
/*   Updated: 2016/08/07 12:04:37 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*ft_list_set(char *data)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	new_list->data = data;
	new_list->prev = NULL;
	new_list->next = NULL;
	return (new_list);
}
