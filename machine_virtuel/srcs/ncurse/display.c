/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:58:08 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/15 14:25:59 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	print_cursor(t_env *e, int x)
{
	int		i;

	i = e->active_process - 1;
	while (i >= 0)
	{
		if (x == e->process[i].position)
		{
			wattron(e->window.memory, COLOR_PAIR(6));
			mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1],
		"%02x", (unsigned int)(unsigned char)tab[x % MEM_SIZE]);
			wattroff(e->window.memory, COLOR_PAIR(6));
		}
		i--;
	}
}

void	print_memory(t_env *e)
{
	if (tab2[e->memory_data[2]] != 0)
	{
		wattron(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
		mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] ,
			"%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
		wattroff(e->window.memory, COLOR_PAIR(tab2[e->memory_data[2]]));
	}
	else if (tab2[e->memory_data[2]] == 0)
		mvwprintw(e->window.memory, e->memory_data[0], e->memory_data[1] ,
			"%02x", (unsigned int)(unsigned char)tab[e->memory_data[2]]);
}

void	write_memory(t_env *e)
{
	while (e->memory_data[2] < MEM_SIZE)
	{
		while (e->flag.pause == 1 && key_hook(e) == 0)
			;
		print_memory(e);
		print_cursor(e, e->memory_data[2]);

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
}

void	check_all_process(t_env *e)
{
	int		x;

	x = e->active_process - 1;
	while (x >= 0)
	{
		if (e->process[x].live_status == 0)
		{
			ft_printf_fd(e->fd, "Le process %d doit etre supprimé\n", x);
			delete_process(e, x);
		}
		else
			e->process[x].live_status = 0;
		x--;
	}
	e->arena.cycle = 0;
	e->flag.live_call = 0;
}

void	update_cycle(t_env *e)
{
	if (!e->active_process)
		vm_error("STOP");
	if (e->arena.cycle == e->flag.cycle_to_die)
	{
		check_all_process(e);
		// e->arena.cycle = 0;
	}
}

void	display_memory(t_env *e)
{
	e->window.memory = newwin(66, 194, 1, 1);
	init_index(&e->memory_data[2], &e->memory_data[0], &e->memory_data[1]);
	write_memory(e);
	while (!memory_run(e))
	{
		write_memory(e);
		e->arena.cycle++;
		if (e->active_process == MAX_PROCESS)
			break ;
		update_cycle(e);
		display_info_menu(e);
	}
}

void	display_delete(t_env *e)
{
	delwin(e->window.tab);
	delwin(e->window.memory);
    delwin(e->window.menu);
}
