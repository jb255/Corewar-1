/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:53:56 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/03 04:32:57 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

extern char g_status_code[17][8];

void	find_next_pc(t_env *e, int x)
{
	char	*label = NULL;
	int		func = -1;
	int		jump_size = 1;

	while (func == -1)
	{
		label = ft_sprintf("%02x", tab[e->process[x].position + jump_size % MEM_SIZE]);
		func = instruct_tab_value(label);
		jump_size++;
	}
	e->process[x].addr_pc = e->process[x].position + jump_size - 1;
}

void	set_process(t_env *e, int process_nb, int x, int creator)
{
	if (e->active_process == process_nb)
		vm_error("Error process attribution");
	init_process(e, process_nb);
	e->process[process_nb].position = x % MEM_SIZE;
	e->process[process_nb].start = x % MEM_SIZE;
	ft_memset(e->process[process_nb].reg, 0, 17);
	e->process[process_nb].reg[1] = -creator;
	e->process[process_nb].id_player = creator;
	find_next_pc(e, process_nb);
}
