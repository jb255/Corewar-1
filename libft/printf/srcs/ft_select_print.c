/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 18:45:28 by vlancien          #+#    #+#             */
/*   Updated: 2016/09/27 21:08:55 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		intlen(int x)
{
	int		i;
	int		c;

	c = abs(x);
	i = 0;
	if (c == 0)
		return (1);
	while (c > 0)
	{
		c = c / 10;
		i++;
	}
	return (x < 0 ? (i + 1) : i);
}

void	ft_select_printable(va_list ap, t_info_str *list, char c)
{
	char	*string;
	int		nb;

	if (c == 's')
	{
		if ((string = va_arg(ap, char*)) == 0)
			ft_putstr("(null)");
		else
			ft_print_string(string, list);
	}
	if (c == 'd')
		ft_print_number((nb = va_arg(ap, int)), list);
}
