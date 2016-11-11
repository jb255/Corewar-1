/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_curse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 17:26:39 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/11 04:12:24 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_CURSE_H
# define N_CURSE_H

# include "corewar.h"
# include "game.h"
# include <ncurses.h>

void	n_curse(t_env *e);
void	draw_borders(WINDOW *screen);

void	init_curse();
void	init_index(int *x, int *y, int *u);

void	display_menu(WINDOW **menu, t_env *e);
void	display_tab(WINDOW **tab, t_env *e);
void	display_memory_color(t_env *e, int y, int x, int u);
void	display_memory(t_env *e);
void	display_init_color(void);
void	display_delete(t_env *e);

void	cycle_downer(t_env *e, int *nb);
void	process_cursor(t_env *e, int y, int addr, int x);

void	memory_exec(t_env *e, int *nb);
void	memory_set_init(t_env *e, int *addr, int *y, int *x);
int		memory_run(t_env *e);

char	*dec_to_hex(unsigned dec, char *hex, int len);


void	apply_func(t_env *e, int xproc, int func);
void	live_func(t_env *e, int xproc, int func);
void	sub_func(t_env *e, int xproc, int func);
void	add_func(t_env *e, int xproc, int func);
#endif
