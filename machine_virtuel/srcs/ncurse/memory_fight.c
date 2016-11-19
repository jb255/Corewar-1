/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:16:37 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 04:59:10 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

extern char	g_status_code[17][8];

void	process_cursor(t_env *e, int y, int addr, int x)
{
	if (addr == e->process[e->memory_data[3]]->position)
	{
		wattron(e->window.memory, COLOR_PAIR(6));
		mvwprintw(e->window.memory, y, x, "%02X", tab[addr % MEM_SIZE]);
		wattroff(e->window.memory, COLOR_PAIR(6));
	}
}

void	exec_process(t_env *e, int xproc)
{
	char	*label;
	char	*size;
	int		jumpx;
	int		func;

	label = to_opcode(tab[e->process[xproc]->position % (MEM_SIZE)],
		tab[(e->process[xproc]->position + 1) % (MEM_SIZE)]);
	func = instruct_tab_value(label);
	size = to_opcode(tab[(e->process[xproc]->position + 2) % (MEM_SIZE)],
		tab[(e->process[xproc]->position + 3) % (MEM_SIZE)]);
	jumpx = jump(ft_atoi(size), g_status_code[func]);
	if (func != 1)
		apply_func(e, xproc, func);
}

void	memory_exec(t_env *e, int *nb)
{
	int		memory_size;

	memory_size = (MEM_SIZE);
	display_menu(&e->window.menu, e);
	while (e->flag.pause == 1 && key_hook(e) == 0)
		;
	wrefresh(e->window.memory);
	if (e->process[*nb]->wait_time - 1 == 0)
	{
		exec_process(e, *nb);
		e->process[*nb]->position = (e->process[*nb]->position
				+ e->process[*nb]->jumptodo) % memory_size;
		find_next_pc(e, *nb);
	}
	usleep(e->flag.time_cycle);
	wrefresh(e->window.menu);
	(*nb)++;
}

void	memory_set_init(t_env *e, int *addr, int *y, int *x)
{
	if (*addr == MEM_SIZE)
		init_index(addr, y, x);
	(void)e;
	// if (*addr % 2 == 0 && *addr != 0)
	// {
	// 	mvwprintw(e->window.memory, *y, *x, " ");
	// 	(*x)++;
	// }
	if (*x >= 191 && (*x = 1))
		(*y)++;
}

int		memory_run(t_env *e)
{
	cycle_downer(e, &e->memory_data[3]);
	while (e->memory_data[3] != e->active_process)
	{
		if (key_hook(e) == 27)
			return (1);
		find_label(e, e->memory_data[3]);
		if (tab2[e->memory_data[2]] == 1){
			wattron(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
			mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] , "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
			wattroff(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
		}
		else
			mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] , "%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
		process_cursor(e, e->memory_data[0], e->memory_data[2], e->memory_data[1]);
		e->memory_data[1] += 3;
		if (e->memory_data[1] >= 191)
		{
			e->memory_data[1] = 1; // retour debut ligne
			e->memory_data[0] += 1; // +1 ligne
		}
		e->memory_data[2]++; // +1 dans le tableau
		if (e->memory_data[2] == (MEM_SIZE))
		{
			wrefresh(e->window.memory);
			nodelay(stdscr, 0);
			getch();

			e->memory_data[1] = 1; // Retour au debut X
			e->memory_data[0] = 1; // Retour au debut Y
			e->memory_data[2] = 0; // Retour au debut Y
		}
		e->memory_data[3]++; // Next process
		// 2 = addr
		// 0 = y
		// 1 = x
		// 3 = nb_proces

	}
	return (0);
}
