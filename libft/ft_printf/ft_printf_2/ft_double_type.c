/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:52:05 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/03 15:52:06 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_double_type(T_LIST *args_data, va_list *args, char **result)
{
	if (!ft_strcmp(args_data->mod, "L"))
		return (ft_call_float(va_arg(*args, long double), args_data, result));
	else
		return (ft_call_float(va_arg(*args, double), args_data, result));
}
