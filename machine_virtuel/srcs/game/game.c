/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:50:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/16 01:09:54 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "function.h"
#include "g_variable.h"
#include "n_curse.h"

int				special_func(t_env *e, int xproc, int func, int list_size)
{
	(void)e;
	(void)xproc;
	if (func == 12 || func == 15)
		list_size = 3;
	else if (func == -1)
		list_size = 1;
	else if (func == 1)
		list_size = 5;
	else if (func == 9 || func == 16)
		list_size = 3;
	return (list_size);
}

void			wait_time_downer(t_env *e, int xproc, int func)
{
	if (func == -1 && e->process[xproc].wait_time != 2)
		e->process[xproc].wait_time = 1;
	else if (e->process[xproc].wait_time <= 1 && func)
		e->process[xproc].wait_time = e->op[func - 1].nb_tours;
	else
		e->process[xproc].wait_time--;
}

t_type_func		find_label(t_env *e, int x)
{
	char		*free_me = NULL;
	t_type_func	list;
	int			func;

	e->process[x].id_player = tab2[e->process[x].position] - 1;
	func = tab[e->process[x].position % MEM_SIZE];
	if (func > 16 || func < 1)
		func = -1;
	list.error = 0;
	if ((func != 1 && func != 12 && func != 15 && func != -1 && func != 9))
	{
		free_me = ft_sprintf("%02x", (unsigned char)tab[(e->process[x].position + 1) % MEM_SIZE]);
		list = check_jump(e, hex_to_bin_quad(free_me), func);
		free(free_me);
	}
	list.func = func;
	list.size = special_func(e, x, func, list.size);
	wait_time_downer(e, x, func);
	return (list);
}
