/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:58:08 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/30 18:27:19 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	write_memory(t_env *e)
{
	int x;

	while (e->memory_data[2] < MEM_SIZE)
	{
		while (e->flag.pause == 1 && key_hook(e) == 0)
			;
		x = 0;
		while (x < e->active_process)
		{
			if (e->memory_data[2] == e->process[x].position)
			{
				wattron(e->window.memory, COLOR_PAIR(6));
				mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1], "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2] % MEM_SIZE]);
				wattroff(e->window.memory, COLOR_PAIR(6));
				wrefresh(e->window.memory);
				// nodelay(stdscr, 0);
				// getch();
			}
			x++;
		}
		if (tab2[e->memory_data[2]] != 0){
			wattron(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
			mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] , "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
			wattroff(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
		}
		else if (tab2[e->memory_data[2]] == 0)
			mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] , "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
		e->memory_data[1] += 3; // Avancement du x
		if (e->memory_data[1] >= 191) // Saut de ligne
		{
			e->memory_data[1] = 1; // retour debut ligne
			e->memory_data[0] += 1; // +1 ligne
		}
		e->memory_data[2]++; // +1 dans le tableau
	}
	wrefresh(e->window.memory);
	e->memory_data[0] = 1;
	e->memory_data[1] = 1;
	e->memory_data[2] = 0;
	// nodelay(stdscr, 0);
	// getch();
}

void	display_memory(t_env *e)
{
	e->window.memory = newwin(66, 194, 1, 1);
	init_index(&e->memory_data[2], &e->memory_data[0], &e->memory_data[1]);
	write_memory(e);
	while (!memory_run(e))
	{
		write_memory(e);
		e->arena.cycle--;
		display_info_menu(e);
	}
}

void	display_delete(t_env *e)
{
	delwin(e->window.tab);
	delwin(e->window.memory);
    delwin(e->window.menu);
}
