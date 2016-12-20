/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:52:00 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 04:40:04 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "n_curse.h"

void	init_curse(t_env *e)
{
	int n;

	n = 0;
	while (n < MEM_SIZE)
	{
		g_tab[n] = 0;
		g_tab2[n] = 0;
		n++;
	}
	e->arena.live_call = 0;
	e->flag.is_decremented = 0;
	e->arena.cycle_total = 0;
	e->arena.cycle_to_die = CYCLE_TO_DIE;
	e->arena.cycle = 0;
	e->flag.pause = 0;
	e->arena.time_cycle = 1;
}

void	init_process(t_env *e, int nb)
{
	e->process[nb].start = 0;
	e->process[nb].position = 0;
	e->process[nb].jumptodo = 0;
	e->process[nb].carry = 0;
	e->process[nb].id_player = 0;
	e->process[nb].wait_time = 0;
	e->process[nb].addr_pc = 0;
	e->process[nb].live_status = 0;
	ft_memset(e->process[nb].reg, 0, 17);
}

void	init_index(int *addr, int *y, int *x)
{
	*y = 1;
	*x = 1;
	*addr = 0;
}
