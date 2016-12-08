/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_curse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 17:19:56 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 16:42:08 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	draw_borders(WINDOW *screen)
{
	int x, y, i;

	getmaxyx(screen, y, x);
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	for (i = 1; i < (y - 1); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	}
	for (i = 1; i < (x - 1); i++) {
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}

void	set_default(void)
{
	initscr();
	cbreak();
	nodelay(stdscr, 0);
	// raw();
	noecho();
	curs_set(0);
}

void	n_curse(t_env *e)
{
	set_default();
	e->flag.obo = 1;
	display_init_color();
    refresh();
	display_menu(e);
	display_tab(&e->window.tab, e);
	display_memory(e);
	display_delete(e);
    endwin();
}
