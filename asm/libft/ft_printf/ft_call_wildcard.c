/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:51:01 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/05 16:49:28 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_call_wildcard(T_LIST *trail, char **print)
{
	char	*result;
	int		state_value;

	state_value = 1;
	result = (trail->format) ? ft_strset(ft_strnew(1), 1, trail->format) :
		ft_strnew(0);
	if (!trail->format)
		trail->width--;
	result = ft_set_width(result, trail);
	*print = ft_repstr(*print, trail->start_index, trail->end_index + 1,
		result);
	ft_move_index(&trail, trail->start_index - trail->end_index +
		ft_strlen(result) - 1);
	free(result);
	return (state_value);
}
