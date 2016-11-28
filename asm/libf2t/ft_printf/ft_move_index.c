/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:54:00 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/03 15:54:01 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_move_index(T_LIST **trail, int padding)
{
	T_LIST	*tmp;

	tmp = *trail;
	while (tmp != NULL)
	{
		tmp->start_index += padding;
		tmp->end_index += padding;
		tmp = tmp->next;
	}
}
