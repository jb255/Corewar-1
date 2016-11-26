/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_curse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 17:26:39 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 04:41:15 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_CURSE_H
# define N_CURSE_H

# include "corewar.h"
# include "game.h"
# include "function.h"
# include <ncurses.h>

void	n_curse(t_env *e);
void	draw_borders(WINDOW *screen);

void	init_curse();
void	init_index(int *x, int *y, int *u);

void	display_menu(t_env *e);
void	display_tab(WINDOW **tab, t_env *e);
void	display_memory_color(t_env *e, int y, int x, int u);
void	display_memory(t_env *e);
void	display_init_color(void);
void	display_delete(t_env *e);

void	cycle_downer(t_env *e, int *nb);
void	process_cursor(t_env *e, int y, int addr, int x);

void	memory_exec(t_env *e, int nb);
void	memory_set_init(t_env *e, int *addr, int *y, int *x);
int		memory_run(t_env *e);

char	*dec_to_hex(unsigned dec, char *hex, int len);
char	*get_op_str(char c, char c1);
void	apply_func(t_env *e, int xproc, t_type_func list);
// char	*get_opfrom_x(t_env *e, int a, int x);
t_type_func check_jump(t_env *e, char *op_size);
char	*to_tab(char *str);
void	display_info_menu(t_env *e);
char	*get_x_from_position(t_env *e, int xproc, int from, int at);
void	write_memory(t_env *e);
#endif
