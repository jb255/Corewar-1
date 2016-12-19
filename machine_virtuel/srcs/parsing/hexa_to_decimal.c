/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_to_decimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 22:11:14 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 01:39:49 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	hex_to_dec(const char *str)
{
	unsigned int	total;
	int				i;

	total = 0;
	i = 0;
	while (0 < str[i] && str[i] < 33)
		i++;
	while ((str[i] >= '0' && str[i] <= '9') ||
	(str[i] >= 'A' && str[i] <= 'F') ||
	(str[i] >= 'a' && str[i] <= 'f'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			total = (total * 16) + (str[i++] - '0');
		if (str[i] >= 'A' && str[i] <= 'F')
			total = (total * 16) + (str[i++] - 'A' + 10);
		if (str[i] >= 'a' && str[i] <= 'f')
			total = (total * 16) + (str[i++] - 'a' + 10);
	}
	return (total);
}
