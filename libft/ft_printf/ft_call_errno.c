/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_errno.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:50:24 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 11:32:23 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_call_errno(T_LIST *trail, char **print)
{
	char	*result;
	int		state_value;

	state_value = 1;
	result = strerror(errno);
	result = ft_set_length(trail, result);
	result = ft_set_width(result, trail);
	*print = ft_repstr(*print, trail->start_index, trail->end_index + 1,
			result);
	ft_move_index(&trail, trail->start_index - trail->end_index +
			ft_strlen(result) - 1);
	free(result);
	return (state_value);
}
