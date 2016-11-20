/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_crossroad.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:11:52 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/05 15:13:49 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_type_crossroad(T_LIST *args_d, va_list *args, char **res)
{
	if (args_d->type == INT_TYPE)
		return (ft_int_type(args_d, args, res));
	else if (args_d->type == CHAR_TYPE)
		return (ft_char_type(args_d, args, res));
	else if (args_d->type == POINTER_TYPE)
		return (ft_call_pointer(va_arg(*args, unsigned long), args_d, res));
	else if (args_d->type == STRING_TYPE && args_d->mod[0] == '-')
		return (ft_call_wstring((ft_conv_wchar(va_arg(*args, char*))), args_d,
			res, 0));
	else if (args_d->type == WSTRING_TYPE ||
			(args_d->type == STRING_TYPE &&
				!ft_strcmp(args_d->mod, "l")))
		return (ft_call_wstring(va_arg(*args, wchar_t*), args_d, res, 1));
	else if (args_d->type == DOUBLE_TYPE)
		return (ft_double_type(args_d, args, res));
	else if (args_d->type == ERRNO)
		return (ft_call_errno(args_d, res));
	else if (args_d->type == PERCENT)
		return (ft_call_percent(args_d, res));
	else if (args_d->incomplete)
		return (ft_call_wildcard(args_d, res));
	else
		return (0);
}
