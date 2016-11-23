/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:16:37 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/23 09:41:39 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

extern char	g_status_code[17][8];

// void	exec_process(t_env *e, int xproc)
// {
	// char		*label;
	// t_type_func	list;
	// int			func;
	// char		*free_me;
	//
	// label = to_tab(ft_itoa_base(tab[e->process[xproc]->position], 16));
	// func = instruct_tab_value(label);
	// if (func > 9)
	// 	func--;
	// printf("FUNC %d\n", func);
	// free_me = to_tab(ft_itoa_base(tab[(e->process[xproc]->position + 1) % MEM_SIZE], 16));
	// list = check_jump(e, hex_to_bin_quad(free_me));
	// free(free_me);
	// if (func != 1)
		// apply_func(e, xproc, func);
// }

int		memory_run(t_env *e)
{
	t_type_func		list;
	// mvwprintw(e->window.menu, 3, 180, "%d", e->arena.cycle);
	// while (e->memory_data[3] != e->active_process)
	// {
		if (key_hook(e) == 27)
			return (1);


		e->memory_data[3] = 0;
		while (e->memory_data[3] < e->active_process)
		{
			if (e->memory_data[2] == e->process[e->memory_data[3]]->position)
			{
				wattron(e->window.memory, COLOR_PAIR(6));
				mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1], "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2] % MEM_SIZE]);
				wattroff(e->window.memory, COLOR_PAIR(6));
				wrefresh(e->window.memory);
			}
			else if (tab2[e->memory_data[2]] != 0){
				wattron(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
				mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] , "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
				wattroff(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
			}
			else if (tab2[e->memory_data[2]] == 0)
				mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] , "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
			e->memory_data[3]++;
		}
		e->memory_data[1] += 3; // Avancement du x
		if (e->memory_data[1] >= 191) // Saut de ligne
		{
			e->memory_data[1] = 1; // retour debut ligne
			e->memory_data[0] += 1; // +1 ligne
		}
		e->memory_data[2]++; // +1 dans le tableau
		if (e->memory_data[2] == (MEM_SIZE)) // Fin du check du tableau
		{
			while (e->flag.pause == 1 && key_hook(e) == 0)
				;
			e->memory_data[3] = 0;
			while (e->memory_data[3] < e->active_process)
			{
				list = find_label(e, e->memory_data[3]);
				if (e->process[e->memory_data[3]]->wait_time - 1 == 0)
				{
					// printf("PROCESS JUMPTO DO %d       \n", e->process[e->memory_data[3]]->jumptodo);
					e->process[e->memory_data[3]]->position = (e->process[e->memory_data[3]]->position + e->process[e->memory_data[3]]->jumptodo) % MEM_SIZE;
					e->process[e->memory_data[3]]->wait_time = 0;
					e->arena.cycle--;
					display_info_menu(e);
				}
				e->memory_data[3]++;
			}
			e->memory_data[0] = 1; // Retour au debut Y
			e->memory_data[1] = 1; // Retour au debut X
			e->memory_data[2] = 0; // Retour au debut Y
			// x++; // Next process
		}
		// 2 = addr
		// 0 = y
		// 1 = x
		// 3 = nb_proces
	// }
	// wrefresh(e->window.memory);


	return (0);
}
