/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 23:02:29 by vlancien          #+#    #+#             */
/*   Updated: 2016/09/27 21:08:29 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*convert_char(wchar_t c)
{
	char		*str;

	str = (char *)malloc(sizeof(char) * (2));
	str[0] = c;
	str[1] = '\0';
	if (c == 0)
		ft_putchar(0);
	return (str);
}

void			ft_putclist(wchar_t c, t_info_str *list)
{
	(void)list;
	ft_putstr(convert_char(c));
}
