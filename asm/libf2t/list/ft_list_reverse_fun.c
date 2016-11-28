/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:16:59 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/28 17:17:00 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	ft_list_reverse_fun(t_list *begin_list)
{
	t_list	*new;
	int		count;

	new = NULL;
	count = ft_list_size(begin_list);
	while (begin_list && count != 1)
	{
		while (begin_list)
		{
			ft_list_push_front(&new, begin_list->data);
			begin_list = begin_list->next;
		}
		count--;
	}
	return (*new);
}
