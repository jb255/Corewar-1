/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_from.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 19:10:32 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/07 20:13:57 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	write_from_tab2(int position, int size, int id)
{
	int		index;

	index = 0;
	position < 0 ? position = MEM_SIZE + position : position;
	position = position % MEM_SIZE;
	while (index < size)
	{
		tab2[position % MEM_SIZE] = id;
		position++;
		if (position == MEM_SIZE)
			position = 0;
		index++;
	}
}
