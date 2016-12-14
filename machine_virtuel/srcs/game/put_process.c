/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:53:56 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/14 15:23:02 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

extern char g_status_code[17][8];

void	delete_process(t_env *e, int process_nb)
{
	t_process	temp;
	int			index;

	index = process_nb + 1;
	while (index < e->active_process)
	{
		temp = e->process[index];
		e->process[index - 1] = temp;
		index++;
	}
	e->active_process--;
}

void	set_process(t_env *e, int process_nb, int x, int creator)
{
	int		i;

	i = 0;
	if (e->active_process == process_nb)
		vm_error("Error process attribution");
	init_process(e, process_nb);
	e->process[process_nb].position = x % MEM_SIZE;
	e->process[process_nb].start = x % MEM_SIZE;
	e->process[process_nb].wait_time = 1;
	// e->process[process_nb].wait_time = e->process[creator].wait_time;
	ft_memset(e->process[process_nb].reg, 0, 17);
	while (i < 17)
	{
		e->process[process_nb].reg[i] = e->process[creator].reg[i];
		i++;
	}
	e->process[process_nb].id_player = creator;
	e->process[process_nb].carry = e->process[creator].carry;
}
