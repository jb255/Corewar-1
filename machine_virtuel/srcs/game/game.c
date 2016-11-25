/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:50:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/25 09:04:49 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "function.h"
#include "g_variable.h"
#include "n_curse.h"

// 10 01 00 00
// 90
// dircode{2},
// 02 90 ff ff ff fa 03

// 01 Registre, Suivie d’un octet (le numéro de registre)
// 10 Direct, Suivie de DIR_SIZE octets (la valeur directement)
// 11 Indirect, Suivie de IND_SIZE octets (la valeur de l’indirection)

// # define REG_CODE				1
// # define DIR_CODE				2
// # define IND_CODE				3



t_type_func		find_label(t_env *e, int x)
{
	int		wait_time[17] = {0, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};
	char	*label;
	t_type_func	list;
	int		func;
	char	*free_me;

	label = to_tab(ft_itoa_base(tab[e->process[x]->position % MEM_SIZE], 16));
	func = instruct_tab_value(label);
	if (func > 9)
		func -= 1;
	free_me = to_tab(ft_itoa_base(tab[(e->process[x]->position + 1) % MEM_SIZE], 16));
	list = check_jump(e, hex_to_bin_quad(free_me));
	if (tab[(e->process[x]->position + 1) % MEM_SIZE] == 144 && func == 2)
		list.size += 2;
	if (func == 12)
		list.size = 3;
	if (func == -1)
		list.size = 1;
	if (func == 1)
		list.size = 5;
	free(free_me);
	e->process[x]->jumptodo = list.size;
	// nodelay(stdscr, 0);
	// getch();
	// nodelay(stdscr, 1);
	list.func = func;
	if (func == -1 && e->process[x]->wait_time != 2)
		e->process[x]->wait_time = 1;
	else if (e->process[x]->wait_time <= 1 && func)
		e->process[x]->wait_time = wait_time[func];
	else
		e->process[x]->wait_time--;
	return (list);
	// printf("func=%d, List size%d\n", func,e->process[x]->wait_time);
}
