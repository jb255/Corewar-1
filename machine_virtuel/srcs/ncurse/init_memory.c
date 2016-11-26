/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:52:00 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 03:41:24 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "n_curse.h"

void	init_curse()
{
	int n;

	n = 0;
	while (n < MEM_SIZE)
	{
		tab[n] = 0;
		tab2[n] = 0;
		tab3[n] = '-';
		n++;
	}

}

void			init_process(t_env *e, int nb)
{
	// e->process[nb] = malloc(sizeof(t_process));
	// printf("%p\n", e->process[nb]);
	e->flag.time_cycle = 10000;
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
