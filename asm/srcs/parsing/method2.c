/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 04:41:34 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/19 04:42:09 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			coerence_str_optab(char *str, t_env *e)
{
	if ((str[0]) == 'r')
	{
		e->method_total += 1;
		return (1);
	}
	else if ((str[0]) == '%' && ((str[1] == ':') ||
		((ft_strlen(str) < 5) && str[1] != '0' && str[1] != '1')))
	{
		e->method_total += 2;
		return (10);
	}
	else if ((str[0]) == '%')
	{
		e->method_total += 4;
		return (10);
	}
	else
	{
		e->method_total += 2;
		return (11);
	}
}

void		push_tail_method(t_line **begin, char **tab, int nb_arg, t_env *e)
{
	t_line		*list;

	list = *begin;
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = create_method(tab, nb_arg, e);
	}
	else
		*begin = create_method(tab, nb_arg, e);
}
