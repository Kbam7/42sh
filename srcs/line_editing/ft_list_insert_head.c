/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_insert_head.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmack <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 10:11:01 by tmack             #+#    #+#             */
/*   Updated: 2016/08/07 12:04:16 by tmack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_list	*ft_list_insert_head(char *data, t_list **head)
{
	t_list	*new_list;

	new_list = ft_list_set(data);
	if (*head == NULL)
	{
		*head = new_list;
		return (*head);
	}
	(*(head))->prev = new_list;
	new_list->next = *head;
	*head = new_list;
	return (*head);
}
