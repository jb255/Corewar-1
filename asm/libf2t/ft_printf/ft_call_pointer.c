/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:50:52 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 17:47:30 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_call_pointer(unsigned long pointer, T_LIST *trail, char **print)
{
	char	*result;
	int		state_value;
	char	*insert;

	state_value = 1;
	if (trail->width < 0)
	{
		trail->width = -1 * trail->width;
		trail->minus = 1;
	}
	result = ft_ubase(pointer, 16);
	result = ft_set_length(trail, result);
	insert = ft_strdup("0x");
	result = ft_repstr(result, 0, 0, insert);
	free(insert);
	if (trail->alternate && pointer == 0 && !trail->accuracy)
		result[2] = 0;
	result = ft_set_width(result, trail);
	*print = ft_repstr(*print, trail->start_index, trail->end_index + 1,
		result);
	ft_move_index(&trail, trail->start_index - trail->end_index +
		ft_strlen(result) - 1);
	free(result);
	return (state_value);
}
