/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:13:23 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 01:44:57 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	name_menu(t_env *e, int nb)
{
	wattron(e->window.menu, COLOR_PAIR(nb + 1));
	mvwprintw(e->window.menu,
		((nb + 1) * 1.8) + 1, 15, "%s", e->players[nb].name);
	wattroff(e->window.menu, COLOR_PAIR(nb + 1));
}

void	auto_mode(t_env *e)
{
	if (!e->flag.obo)
	{
		wattron(e->window.menu, COLOR_PAIR(10));
		mvwprintw(e->window.menu, 7, 180, "Activated ");
		wattroff(e->window.menu, COLOR_PAIR(10));
	}
	else
	{
		wattron(e->window.menu, COLOR_PAIR(6));
		mvwprintw(e->window.menu, 7, 180, "Disabled  ");
		wattroff(e->window.menu, COLOR_PAIR(6));
	}
}

void	display_info_menu(t_env *e)
{
	mvwprintw(e->window.menu, 1, 165, "CYCLE_TO_DIE: ");
	mvwprintw(e->window.menu, 2, 165, "CYCLE_DELTA: ");
	mvwprintw(e->window.menu, 3, 165, "CYCLE: ");
	mvwprintw(e->window.menu, 4, 165, "CYCLE T: ");
	mvwprintw(e->window.menu, 5, 165, "PROCESS: ");
	mvwprintw(e->window.menu, 6, 165, "TIME_SPEED: ");
	mvwprintw(e->window.menu, 7, 165, "[P]AUTO MODE: ");
	if (e->flag.pause)
		mvwprintw(e->window.menu, 4, 125, "PAUSED");
	else
		mvwprintw(e->window.menu, 4, 125, "      ");
	wattron(e->window.menu, COLOR_PAIR(5));
	mvwprintw(e->window.menu, 1, 180, "%d    ", e->arena.cycle_to_die);
	mvwprintw(e->window.menu, 2, 180, "%d    ", CYCLE_DELTA);
	mvwprintw(e->window.menu, 3, 180, "%d    ", e->arena.cycle);
	mvwprintw(e->window.menu, 4, 180, "%d    ", e->arena.cycle_total);
	mvwprintw(e->window.menu, 5, 180, "%d    ", e->active_process);
	mvwprintw(e->window.menu, 6, 180, "x%d    ", e->arena.time_cycle);
	auto_mode(e);
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
		mvwprintw(e->window.menu, ((nb + 1) * 1.8) + 1, 1, "Joueur %d[%d]: ",
		nb + 1, e->players[nb].id_live);
		wattroff(e->window.menu, COLOR_PAIR(5));
		mvwprintw(e->window.menu, ((nb + 1) * 1.8) + 1, 35, "|");
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
