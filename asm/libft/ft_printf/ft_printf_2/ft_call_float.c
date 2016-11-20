/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:50:31 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 09:22:06 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_call_float(long double number, T_LIST *trail, char **print)
{
	char	*result;
	int		state_value;

	state_value = 1;
	if (trail->format == 'f' || trail->format == 'F')
		result = ft_conv_float(number, (trail->accuracy != -1) ?
				trail->accuracy : 6);
	if (trail->format == 'e' || trail->format == 'E')
		result = ft_conv_exp(number, trail);
	if (trail->format == 'E')
		ft_strtoupper(result);
	result = ft_apply_flag(result, trail);
	result = ft_set_width(result, trail);
	if (trail->alternate)
		result = ft_alternate(result, trail);
	*print = ft_repstr(*print, trail->start_index, trail->end_index + 1,
			result);
	ft_move_index(&trail, trail->start_index - trail->end_index +
		ft_strlen(result) - 1);
	free(result);
	return (state_value);
}
