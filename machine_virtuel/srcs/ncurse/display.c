/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:58:08 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/23 04:31:42 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	display_memory(t_env *e)
{
	e->window.memory = newwin(66, 194, 1, 1);
	// 2 = addr
	// 0 = y
	// 1 = x
	// tab[0] = 8;
	// tab[MEM_SIZE - 100] = 9;
	// tab2[MEM_SIZE - 1] = 1;
	// printf("Process valide %d\n", e->active_process);
	init_index(&e->memory_data[2], &e->memory_data[0], &e->memory_data[1]);
	while (!memory_run(e))
		;
}

void	display_delete(t_env *e)
{
	delwin(e->window.tab);
	delwin(e->window.memory);
    delwin(e->window.menu);
}
