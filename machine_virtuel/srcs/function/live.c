/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/22 06:48:10 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	live_func(t_env *e, int xproc, int func)
{
	int		index;

	index = 0;
	if (func == 1 && !e->process[xproc]->live_status)
	{
		e->process[xproc]->reg[0] = tab2[e->process[xproc]->position % MEM_SIZE];
		index = 2;
		while (index < 9)
		{
			tab[(e->process[xproc]->position + index) % MEM_SIZE] = -1;
			tab2[(e->process[xproc]->position + index) % MEM_SIZE] = e->process[xproc]->reg[0];
			index++;
		}
		// tab[e->process[xproc]->position + 9 % MEM_SIZE] = 'G' - e->process[xproc]->reg[0];
		e->process[xproc]->live_status = 1;
	}
}
