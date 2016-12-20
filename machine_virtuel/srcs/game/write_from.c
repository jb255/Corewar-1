/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_from.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:10:32 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 17:04:20 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void			write_from_tab2(int position, int size, int id)
{
	int		index;

	index = 0;
	position < 0 ? position = MEM_SIZE + position : position;
	position = position % MEM_SIZE;
	while (index < size)
	{
		g_tab2[position % MEM_SIZE] = abs(id);
		position++;
		if (position == MEM_SIZE)
			position = 0;
		index++;
	}
}

void			write_from_x(t_env *e, int from, int data, int octet)
{
	char	*hex;
	int		x;

	hex = NULL;
	(void)e;
	hex = ft_sprintf("%08x", data);
	while (octet > 0)
	{
		x = (from + (4 - octet)) % MEM_SIZE;
		x = x < 0 ? MEM_SIZE + x : x;
		g_tab[x] = octet_precision(hex, 4 - octet);
		octet--;
	}
	if (hex != NULL)
		free(hex);
}
