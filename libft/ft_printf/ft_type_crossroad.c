/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_crossroad.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <mlevieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:11:52 by mlevieux          #+#    #+#             */
/*   Updated: 2016/12/18 22:07:35 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_type_crossroad(T_LIST *args_d, va_list *args, char **res)
{
	int		x;

	x = 0;
	if (args_d->type == INT_TYPE)
		x = ft_int_type(args_d, args, res);
	else if (args_d->type == CHAR_TYPE)
		x = ft_char_type(args_d, args, res);
	else if (args_d->type == POINTER_TYPE)
		x = ft_call_pointer(va_arg(*args, unsigned long), args_d, res);
	else if (args_d->type == STRING_TYPE && args_d->mod[0] == '-')
		x = ft_call_wstring(ft_conv_wchar(va_arg(*args, char*)),
		args_d, res, 0);
	else if (args_d->type == WSTRING_TYPE || (args_d->type == STRING_TYPE &&
		!ft_strcmp(args_d->mod, "l")))
		x = ft_call_wstring(va_arg(*args, wchar_t*), args_d, res, 1);
	else if (args_d->type == DOUBLE_TYPE)
		x = ft_double_type(args_d, args, res);
	else if (args_d->type == ERRNO)
		x = ft_call_errno(args_d, res);
	else if (args_d->type == PERCENT)
		x = ft_call_percent(args_d, res);
	else if (args_d->incomplete)
		x = ft_call_wildcard(args_d, res);
	return (x);
}
