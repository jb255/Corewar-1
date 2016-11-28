/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:18:36 by vlancien          #+#    #+#             */
/*   Updated: 2016/09/27 21:02:09 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	list_sort_type(t_list **begin_list, int (*cmp)())
{
	t_list		*list;
	t_list		*begin;
	int			done;

	list = *begin_list;
	begin = *begin_list;
	done = 1;
	while (done)
	{
		done = 0;
		list = begin;
		while (list->next)
		{
			if (cmp(list->data, list->next->data) > 0)
			{
				ft_lstswap(&list->data, &list->next->data);
				done = 1;
			}
			list = list->next;
		}
	}
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list		*list;
	t_list		*begin;
	int			done;

	list = *begin_list;
	begin = *begin_list;
	done = 1;
	while (done)
	{
		done = 0;
		list = begin;
		while (list->next)
		{
			if (cmp(list->data, list->next->data) > 0)
			{
				ft_lstswap(&list->data, &list->next->data);
				done = 1;
			}
			list = list->next;
		}
	}
}
