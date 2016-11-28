/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:26:19 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/05 17:26:20 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	part_two(T_LIST *a, va_list *args, char **res)
{
	if (!ft_strcmp(a->mod, "h") && !a->is_signed)
		return (ft_call_uint((unsigned short)va_arg(*args, unsigned), a, res));
	else if (!ft_strcmp(a->mod, "h") && a->is_signed)
		return (ft_call_int((short)va_arg(*args, int), a, res));
	else if (!ft_strcmp(a->mod, "j") && !a->is_signed)
		return (ft_call_uint(va_arg(*args, uintmax_t), a, res));
	else if (!ft_strcmp(a->mod, "j") && a->is_signed)
		return (ft_call_int(va_arg(*args, intmax_t), a, res));
	else if (!ft_strcmp(a->mod, "z") && !a->is_signed)
		return (ft_call_uint(va_arg(*args, size_t), a, res));
	else if (!ft_strcmp(a->mod, "z") && a->is_signed)
		return (ft_call_int((size_t)va_arg(*args, long long), a, res));
	else if (!ft_strcmp(a->mod, "-") && !a->is_signed)
		return (ft_call_uint(va_arg(*args, unsigned), a, res));
	else
		return (ft_call_int(va_arg(*args, int), a, res));
}

int			ft_int_type(T_LIST *a, va_list *args, char **res)
{
	if (a->format == 'D')
		return (ft_call_int(va_arg(*args, long), a, res));
	else if (a->format == 'O' || a->format == 'U')
		return (ft_call_uint(va_arg(*args, unsigned long), a, res));
	else if (!ft_strcmp(a->mod, "ll") && !a->is_signed)
		return (ft_call_uint(va_arg(*args, unsigned long long), a, res));
	else if (!ft_strcmp(a->mod, "ll") && a->is_signed)
		return (ft_call_int(va_arg(*args, long long), a, res));
	else if (!ft_strcmp(a->mod, "l") && !a->is_signed)
		return (ft_call_uint(va_arg(*args, unsigned long), a, res));
	else if (!ft_strcmp(a->mod, "l") && a->is_signed)
		return (ft_call_int(va_arg(*args, long), a, res));
	else if (!ft_strcmp(a->mod, "hh") && !a->is_signed)
		return (ft_call_uint((unsigned char)va_arg(*args, unsigned), a, res));
	else if (!ft_strcmp(a->mod, "hh") && a->is_signed)
		return (ft_call_int((char)va_arg(*args, int), a, res));
	else
		return (part_two(a, args, res));
}
