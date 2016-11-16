/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:16:37 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/16 03:38:08 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

extern char	g_status_code[17][8];

void	process_cursor(t_env *e, int y, int addr, int x)
{
	int		process;

	process = 0;
	if (addr == e->process[e->memory_data[2]]->position)
	{
		wattron(e->window.memory, COLOR_PAIR(6));
		mvwprintw(e->window.memory, y, x, "%c%c", tab[addr % ((MEM_SIZE) * 2)],
		tab[addr + 1 % ((MEM_SIZE) * 2)]);
		wattroff(e->window.memory, COLOR_PAIR(6));
		wrefresh(e->window.memory);
	}
}

void	exec_process(t_env *e, int xproc)
{
	char	*label;
	char	*size;
	int		jumpx;
	int		func;

	label = to_opcode(tab[e->process[xproc]->position % (MEM_SIZE * 2)],
		tab[(e->process[xproc]->position + 1) % (MEM_SIZE * 2)]);
	func = instruct_tab_value(label);
	size = to_opcode(tab[(e->process[xproc]->position + 2) % (MEM_SIZE * 2)],
		tab[(e->process[xproc]->position + 3) % (MEM_SIZE * 2)]);
	jumpx = jump(ft_atoi(size), g_status_code[func]);
	if (func != 1)
		apply_func(e, xproc, func);
}

void	memory_exec(t_env *e, int *nb)
{
	int		memory_size;

	memory_size = (MEM_SIZE * 2);
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
	if (*addr == MEM_SIZE * 2)
		init_index(addr, y, x);
	if (*addr % 2 == 0 && *addr != 0)
	{
		mvwprintw(e->window.memory, *y, *x, " ");
		(*x)++;
	}
	if (*x >= 193 && (*x = 1))
		(*y)++;
}

int		memory_run(t_env *e)
{
	cycle_downer(e, &e->memory_data[2]);
	while (e->memory_data[2] != e->active_process)
	{
		if (key_hook(e) == 27)
			return (1);
		memory_set_init(e, &e->memory_data[3], &e->memory_data[0],
			&e->memory_data[1]);
		find_label(e, e->memory_data[2]);
		display_memory_color(e, e->memory_data[0], e->memory_data[3],
			e->memory_data[1]);
		process_cursor(e, e->memory_data[0], e->memory_data[3],
			e->memory_data[1]);
		e->memory_data[3] += 2;
		if (e->memory_data[3] == (MEM_SIZE * 2))
			memory_exec(e, &e->memory_data[2]);
		e->memory_data[1] += 2;
	}
	return (0);
}
