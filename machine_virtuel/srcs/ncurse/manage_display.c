/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 02:36:53 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/16 02:38:19 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

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
	if (e->arena.live_call >= NBR_LIVE)
		e->arena.cycle_to_die -= CYCLE_DELTA;
	e->flag.is_decremented++;
	e->arena.cycle = 0;
	e->arena.live_call = 0;
}

void	update_cycle(t_env *e)
{
	if (!e->active_process)
		victory_player(e);
	if (e->arena.cycle >= e->arena.cycle_to_die)
		check_all_process(e);
	if (e->flag.is_decremented >= MAX_CHECKS)
	{
		e->arena.cycle_to_die -= CYCLE_DELTA;
		e->flag.is_decremented = 0;
	}
}

void	press_start(t_env *e)
{
	int		x;

	x = 1;
	nodelay(stdscr, 1);
	while (key_hook(e) != 32)
	{
		display_info_menu(e);
		wattron(e->window.menu, COLOR_PAIR(++x));
		mvwprintw(e->window.menu, 4, 125, "PRESS SPACE");
		wattroff(e->window.menu, COLOR_PAIR(x));
		wrefresh(e->window.menu);
		mvwprintw(e->window.menu, 4, 125, "           ");
		x = x == 6 ? 1 : x;
	}
}

void	victory_player(t_env *e)
{
	endwin();
	ft_printf("le joueur %d(%s) a gagne\n", e->players[e->arena.winner].id_live,
	e->players[e->arena.winner].name);
	exit(1);
}
