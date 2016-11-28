/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:53:20 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/03 16:11:15 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_is_format(char format)
{
	if (format == 'd' || format == 'D' || format == 'i' || format == 'o' ||
			format == 'u' || format == 'U' || format == 'O' || format == 'x' ||
			format == 'X' || format == 'e' || format == 'E' || format == 'f' ||
			format == 'F' || format == 'p' || format == 'm' || format == 'b' ||
			format == 'c' || format == 'C' || format == 's' || format == 'S' ||
			format == '%')
		return (1);
	return (0);
}
