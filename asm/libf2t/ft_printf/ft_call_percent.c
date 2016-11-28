/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:27:48 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 16:14:01 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_call_percent(T_LIST *trail, char **print)
{
	char	*result;
	int		state_value;

	state_value = 1;
	result = ft_strdup("%");
	if (trail->width < 0)
	{
		trail->width = -1 * trail->width;
		trail->minus = 1;
	}
	result = ft_set_width(result, trail);
	*print = ft_repstr(*print, trail->start_index, trail->end_index + 1,
		result);
	ft_move_index(&trail, trail->start_index - trail->end_index +
		ft_strlen(result) - 1);
	free(result);
	return (state_value);
}
