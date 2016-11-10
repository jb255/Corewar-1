/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:41:37 by jaustry           #+#    #+#             */
/*   Updated: 2016/11/04 21:41:39 by jaustry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_func		*create_label(void *data)
{
	t_func		*list;

	list = NULL;
	list = (t_func *)malloc(sizeof(t_func));
	if (list)
	{
		list->label = data;
		list->next = NULL;
		list->line = NULL;
	}
	return (list);
}

void		push_tail_label(t_func **begin_list, t_func **end_list, void *data)
{
	t_func		*list;

	list = *begin_list;
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = create_label(data);
		*end_list = list->next;
	}
	else
	{
		*begin_list = create_label(data);
		*end_list = *begin_list;
	}
}
