/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:16:52 by vlancien          #+#    #+#             */
/*   Updated: 2016/06/02 23:33:36 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list		*list;
	t_list		*tmp;
	t_list		*tmp2;

	list = *begin_list;
	tmp2 = NULL;
	while (list != NULL)
	{
		tmp = list->next;
		list->next = tmp2;
		tmp2 = list;
		list = tmp;
	}
	*begin_list = tmp2;
}
