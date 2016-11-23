/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:53:56 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/22 06:16:46 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

extern char g_status_code[17][8];

// void	find_next_pc(t_env *e, int x)
// {
// 	char	*label = NULL;
// 	int		func = -1;
// 	int		jump_size;
// 	int		position = e->process[x]->position;
// 	char	*size = NULL;
//
// 	while (func == -1)
// 	{
// 		label = to_opcode(tab[position % ((MEM_SIZE))], tab[(position + 1) % ((MEM_SIZE))]);
// 		func = instruct_tab_value(label);
// 		size = to_opcode(tab[position + 2], tab[position + 3]);
// 		jump_size = jump(ft_atoi(size), g_status_code[func]);
// 		if (func == -1)
// 			position++;
// 		free(label);
// 		free(size);
// 	}
// 	e->process[x]->addr_pc = position + jump_size;
// }

void	set_process(t_env *e, int process_nb, int x, int creator)
{
	if (e->active_process == process_nb)
		vm_error("Error process attribution");
	init_process(e, process_nb);
	e->process[process_nb]->position = x;
	e->process[process_nb]->start = x;
	ft_memset(e->process[process_nb]->reg, 0, 17);
	e->process[process_nb]->reg[1] = x;
	e->process[process_nb]->id_player = creator;
	// find_next_pc(e, process_nb);
}
