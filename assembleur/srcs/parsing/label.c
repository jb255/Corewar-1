/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:41:37 by jaustry           #+#    #+#             */
/*   Updated: 2016/11/20 00:00:24 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

t_func		*create_label(void *data, t_env *e)
{
	t_func		*list;

	list = NULL;
	list = (t_func *)malloc(sizeof(t_func));
	if (data && ft_strlen(data) == 1)
	{
		ft_printf("Error line %d, label must be at least of length 1.\n",
			e->y_line);
		exit(-1);
	}
	if (list)
	{
		list->label = data ? ft_strdup(data) : NULL;
		list->next = NULL;
		list->line = NULL;
		list->line_in_file = e->y_line;
		list->position = e->method_position + e->method_total;
	}
	return (list);
}

void		push_tail_label(t_func **begin_list, t_func **end_list, void *data,
		t_env *e)
{
	t_func		*list;

	list = *begin_list;
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = create_label(data, e);
		*end_list = list->next;
	}
	else
	{
		*begin_list = create_label(data, e);
		*end_list = *begin_list;
	}
}
