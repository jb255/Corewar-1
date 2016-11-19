/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:13:23 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 00:27:07 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	name_menu(t_env *e, int nb)
{
	wattron(e->window.menu, COLOR_PAIR(nb + 1));
	mvwprintw(e->window.menu, ((nb + 1) * 1.8) + 1, 12, "%s", e->players[nb].name);
	wattroff(e->window.menu, COLOR_PAIR(nb + 1));
}

void	display_info_menu(WINDOW **menu, t_env *e)
{
	(void)e;
	mvwprintw(*menu, 1, 165, "CYCLE_TO_DIE: ");
	mvwprintw(*menu, 2, 165, "CYCLE_DELTA: ");
	mvwprintw(*menu, 3, 165, "CYCLE: ");
	mvwprintw(*menu, 4, 165, "PROCESS: ");
	mvwprintw(*menu, 5, 165, "TIME_CYCLE: ");
	if (e->flag.pause)
		mvwprintw(*menu, 4, 125, "PAUSED");
	wattron(e->window.menu, COLOR_PAIR(5));
	mvwprintw(*menu, 1, 180, "%d", CYCLE_TO_DIE);
	mvwprintw(*menu, 2, 180, "%d", CYCLE_DELTA);
	mvwprintw(*menu, 3, 180, "%d", e->arena.cycle);
	mvwprintw(*menu, 4, 180, "%d", e->active_process);
	mvwprintw(*menu, 5, 180, "%d", e->flag.time_cycle);
	wattroff(e->window.menu, COLOR_PAIR(5));
	wrefresh(*menu);
}

void	display_menu(WINDOW **menu, t_env *e)
{
	int		nb;

	nb = 0;
	*menu = newwin(10, 196, 68, 0);
	draw_borders(*menu);
	display_info_menu(menu, e);
	while (nb < e->active_players)
	{
		wattron(*menu, COLOR_PAIR(5));
		mvwprintw(*menu, ((nb + 1) * 1.8 ) + 1 , 1, "Joueur %d: ", nb + 1);
		wattroff(*menu, COLOR_PAIR(5));
		mvwprintw(*menu, ((nb + 1) * 1.8 ) + 1 , 35, "|");
		name_menu(e, nb);
		nb++;
	}
	wrefresh(*menu);
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
	mvwprintw(e->window.memory, y, x , "%02X", tab[addr]);
}
