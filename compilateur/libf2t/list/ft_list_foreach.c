/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:17:07 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/28 17:17:08 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list		*list;

	list = begin_list;
	if (!list)
		return ;
	while (list)
	{
		(*f)(list->data);
		list = list->next;
	}
}
