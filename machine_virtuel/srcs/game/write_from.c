/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_from.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:10:32 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/06 17:00:48 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	write_from_tab2(int position, int size, int id)
{
	int		index;

	index = (position + size) % MEM_SIZE;
	if (position == MEM_SIZE)
		position = 0;
	while (position != index)
	{
		tab2[position] = id;
		position++;
		if (position == MEM_SIZE)
			position = 0;
	}
}
