/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:00:39 by kbamping          #+#    #+#             */
/*   Updated: 2016/06/19 17:00:43 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **begin_list)
{
	t_list	*tmp;
	t_list	*tmp1;
	t_list	*tmp2;

	tmp = NULL;
	tmp = *begin_list;
	if (tmp == NULL || tmp->next == NULL)
		return ;
	tmp1 = tmp->next;
	tmp2 = tmp1->next;
	tmp->next = NULL;
	tmp1->next = tmp;
	while (tmp2)
	{
		tmp = tmp1;
		tmp1 = tmp2;
		tmp2 = tmp2->next;
		tmp1->next = tmp;
	}
	*begin_list = tmp1;
}
