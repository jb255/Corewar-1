/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 18:45:28 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/22 06:28:16 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


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
