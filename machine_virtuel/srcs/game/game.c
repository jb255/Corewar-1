/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:50:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 15:30:48 by vlancien         ###   ########.fr       */
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
	// if (tab[(e->process[xproc].position + 1) % MEM_SIZE] == 144 && func == 2)
	// 	list_size += 2;
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
	int			wait_time[17] = {0, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 1};

	if (func == -1 && e->process[xproc].wait_time != 2)
		e->process[xproc].wait_time = 1;
	else if (e->process[xproc].wait_time <= 1 && func)
		e->process[xproc].wait_time = wait_time[func];
	else
		e->process[xproc].wait_time--;
	// ft_printf_fd(e->fd, "--->Waiting time downer process %d:  [%d]\nProcess is at %d\n", xproc, e->process[xproc].wait_time, e->process[xproc].position);
}

t_type_func		find_label(t_env *e, int x)
{
	char		*label = NULL;
	char		*free_me = NULL;
	t_type_func	list;
	int			func;

	e->process[x].id_player = tab2[e->process[x].position] - 1;
	label = ft_sprintf("%02x", tab[e->process[x].position % MEM_SIZE]);
	func = instruct_tab_value(label);
	if ((func != 1 && func != 12 && func != 15 && func != -1 && func != 9) || label == NULL)
	{
		free_me = ft_sprintf("%02x", tab[(e->process[x].position + 1) % MEM_SIZE]);
		list = check_jump(e, hex_to_bin_quad(free_me), func);
		// ft_printf_fd(e->fd, "-->Verification de la fonction [%d]size{%d}\n", func, list.size);
		free(free_me);
	}
	list.size = special_func(e, x, func, list.size);
	list.func = func;
	wait_time_downer(e, x, func);
	free(label);
	return (list);
}
