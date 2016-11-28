/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 13:01:50 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 16:55:50 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_strtoupper(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

int		ft_call_uint(uintmax_t number, T_LIST *trail, char **print)
{
	char	*result;
	int		state_value;

	state_value = 1;
	result = ft_ubase(number, trail->format);
	if (trail->width < 0)
	{
		trail->width = -1 * trail->width;
		trail->minus = 1;
	}
	if (trail->format == 'X')
		ft_strtoupper(result);
	result = ft_apply_flag(result, trail);
	result = ft_set_length(trail, result);
	if (trail->alternate && !(number == 0 && trail->accuracy))
		result = ft_alternate(result, trail);
	result = ft_set_width(result, trail);
	*print = ft_repstr(*print, trail->start_index, trail->end_index + 1,
			result);
	ft_move_index(&trail, trail->start_index - trail->end_index +
			ft_strlen(result) - 1);
	free(result);
	return (state_value);
}

int		ft_call_int(intmax_t number, T_LIST *trail, char **print)
{
	char	*result;
	int		state_value;

	state_value = 1;
	result = ft_base(number, trail->format);
	if (number != 0 && trail->alternate)
		result = ft_alternate(result, trail);
	if (trail->width < 0)
	{
		trail->width = -1 * trail->width;
		trail->minus = 1;
	}
	result = ft_apply_flag(result, trail);
	result = ft_set_length(trail, result);
	result = ft_set_width(result, trail);
	*print = ft_repstr(*print, trail->start_index, trail->end_index + 1,
			result);
	ft_move_index(&trail, trail->start_index - trail->end_index +
			ft_strlen(result) - 1);
	free(result);
	return (state_value);
}
