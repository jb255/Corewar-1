/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 13:56:58 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/03 15:52:43 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_get_fmt(T_LIST *trail, char fmt)
{
	if (fmt == 'd' || fmt == 'i' || fmt == 'D')
		trail->is_signed = 1;
	if (fmt == 'd' || fmt == 'i' || fmt == 'o' || fmt == 'u' || fmt == 'D' ||
		fmt == 'O' || fmt == 'x' || fmt == 'X' || fmt == 'U' || fmt == 'b')
		trail->type = 'd';
	else if (fmt == 'e' || fmt == 'E' || fmt == 'f' || fmt == 'F')
		trail->type = 'f';
	else if (fmt == 'c' || fmt == 'C')
		trail->type = 'c';
	else
		trail->type = fmt;
	trail->format = fmt;
}
