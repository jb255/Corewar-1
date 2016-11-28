/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:51:23 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/05 15:18:22 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#define W wchar_t

int		ft_char_type(T_LIST *args_data, va_list *args, char **res)
{
	if (args_data->format == 'C' || (args_data->format == 'c' &&
				!ft_strcmp(args_data->mod, "l")))
		return (ft_call_char((W)va_arg(*args, W), args_data, res));
	else
		return (ft_call_char((char)va_arg(*args, W), args_data, res));
}
