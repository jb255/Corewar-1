/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 22:12:43 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/22 06:12:54 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	g_dec_to_hex[17] = "0123456789ABCDEF";

int		get_dec(unsigned dec)
{
	int		size;

	if (dec & 0xFFFF0000)
	{
		if (dec & 0xFF000000)
			size = dec & 0xF0000000 ? 8 : 7;
		else
			size = dec & 0x00F00000 ? 6 : 5;
	}
	else if (dec & 0x0000FF00)
		size = dec & 0x0000F000 ? 4 : 3;
	else if (dec & 0x000000FF)
		size = dec & 0x000000F0 ? 2 : 1;
	else
		size = 1;
	return (size);
}

char	*dec_to_hex(unsigned dec, char *hex, int len)
{
	char	*hex2;
	char	*end;
	char	*c;
	char	*s;

	if (hex == NULL)
	{
		len = get_dec(dec);
		hex = malloc((len + 1) * sizeof(char));
	}
	hex2 = hex + len;
	*hex2 = '\0';
	c = hex;
	s = hex2;
	end = hex2;
	--hex2;
	while (hex2--)
	{
		*hex2 = g_dec_to_hex[dec & 0xF];
		dec >>= 4;
		if (dec == 0)
			break ;
	}
	if (ft_strlen(hex2) == 3)
		hex2[2] = '\0';
	return (hex2);
}
