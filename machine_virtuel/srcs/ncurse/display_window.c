/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:13:23 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/23 04:35:23 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	name_menu(t_env *e, int nb)
{
	wattron(e->window.menu, COLOR_PAIR(nb + 1));
	mvwprintw(e->window.menu, ((nb + 1) * 1.8) + 1, 12, "%s", e->players[nb].name);
	wattroff(e->window.menu, COLOR_PAIR(nb + 1));
}

void	display_info_menu(t_env *e)
{
	(void)e;
	mvwprintw(e->window.menu, 1, 165, "CYCLE_TO_DIE: ");
	mvwprintw(e->window.menu, 2, 165, "CYCLE_DELTA: ");
	mvwprintw(e->window.menu, 3, 165, "CYCLE: ");
	mvwprintw(e->window.menu, 4, 165, "PROCESS: ");
	mvwprintw(e->window.menu, 5, 165, "TIME_CYCLE: ");
	if (e->flag.pause)
		mvwprintw(e->window.menu, 4, 125, "PAUSED");
	wattron(e->window.menu, COLOR_PAIR(5));
	mvwprintw(e->window.menu, 1, 180, "%d", CYCLE_TO_DIE);
	mvwprintw(e->window.menu, 2, 180, "%d", CYCLE_DELTA);
	mvwprintw(e->window.menu, 3, 180, "%d", e->arena.cycle);
	mvwprintw(e->window.menu, 4, 180, "%d", e->active_process);
	mvwprintw(e->window.menu, 5, 180, "%d", e->flag.time_cycle);
	wattroff(e->window.menu, COLOR_PAIR(5));
	wrefresh(e->window.menu);
}

void	display_menu(t_env *e)
{
	int		nb;

	nb = 0;
	e->window.menu = newwin(10, 196, 68, 0);
	draw_borders(e->window.menu);
	display_info_menu(e);
	while (nb < e->active_players)
	{
		wattron(e->window.menu, COLOR_PAIR(5));
		mvwprintw(e->window.menu, ((nb + 1) * 1.8 ) + 1 , 1, "Joueur %d: ", nb + 1);
		wattroff(e->window.menu, COLOR_PAIR(5));
		mvwprintw(e->window.menu, ((nb + 1) * 1.8 ) + 1 , 35, "|");
		name_menu(e, nb);
		nb++;
	}
	wrefresh(e->window.menu);
}

void	display_tab(WINDOW **tab, t_env *e)
{
	(void)e;
	*tab = newwin(68, 196, 0, 0);
	draw_borders(*tab);
	wrefresh(*tab);
}

void	display_memory_color(t_env *e, int y, int addr, int x)
{
	// if (tab2[addr] >= 1 && tab2[addr] <= 4)
	// {
	// 	wattron(e->window.memory, COLOR_PAIR(tab2[addr]));
	// 	mvwprintw(e->window.memory, y, x , "%c%c", tab[addr], tab[addr + 1]);
	// 	wattroff(e->window.memory, COLOR_PAIR(tab2[addr]));
	// }
	// else
	// mvwprintw(e->window.memory, y, x , "%c%c", tab[addr], tab[addr + 1]);
	// printf("%d %d, %d\n", y,x, addr);
	mvwprintw(e->window.memory, y, x , "%02x", tab[addr]);
}
