/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:50:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/30 13:41:52 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "function.h"
#include "g_variable.h"
#include "n_curse.h"

int		(*g_func_check[16])(t_env*, int, t_type_func) = {check_live, check_ld, check_st, check_add, check_add, check_and, check_or, check_xor, check_live, check_live, check_live, check_live, check_live, check_live, check_live, check_live};

int				func_valid(t_env *e, t_type_func list, int func)
{
	ft_putstr_fd("Check de la fonction\n", e->fd);
	if (func == 2 && (!list.type[1].t_reg || (!list.type[0].t_ind && !list.type[0].t_dir) || list.type[0].t_reg))
		return (-1);
	if (func == 3 && (!list.type[0].t_reg || (!list.type[1].t_reg && !list.type[1].t_ind)))
		return (-1);
	if ((func == 4 || func == 5) && (!list.type[0].t_reg || !list.type[1].t_reg || !list.type[2].t_reg))
		return (-1);
	if ((func == 6 || func == 7 || func == 8) && ((!list.type[0].t_reg && !list.type[0].t_ind && !list.type[0].t_dir) || (!list.type[1].t_reg && !list.type[1].t_ind && !list.type[1].t_dir) || !list.type[2].t_reg))
		return (-1);
	return (0);
}

int				special_func(t_env *e, int xproc, int func, int list_size)
{
	if (tab[(e->process[xproc].position + 1) % MEM_SIZE] == 144 && func == 2)
		list_size += 2;
	else if (func == 12)
		list_size = 3;
	else if (func == -1)
		list_size = 1;
	else if (func == 1)
		list_size = 5;
	return (list_size);
}

void			wait_time_downer(t_env *e, int xproc, int func)
{
	int			wait_time[17] = {0, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

	if (func == -1 && e->process[xproc].wait_time != 2)
		e->process[xproc].wait_time = 1;
	else if (e->process[xproc].wait_time <= 1 && func)
		e->process[xproc].wait_time = wait_time[func];
	else
		e->process[xproc].wait_time--;
	ft_printf_fd(e->fd, "--->Waiting time downer:  [%d]\n", e->process[xproc].wait_time);
}

t_type_func		find_label(t_env *e, int x)
{
	char		*label = NULL;
	char		*free_me = NULL;
	t_type_func	list;
	int			func;

	label = ft_sprintf("%02x", tab[e->process[x].position % MEM_SIZE]);
	func = instruct_tab_value(label);
	func > 9 ? (func -= 1) : func;
	if ((func != 1 && func != 12 && func != -1) || label == NULL)
	{
		free_me = ft_sprintf("%02x", tab[(e->process[x].position + 1) % MEM_SIZE]);
		list = check_jump(e, hex_to_bin_quad(free_me));
		if (!g_func_check[func - 1](e, x, list))
			func = -1;
		if (func_valid(e, list, func) == -1)
			func = -1;
		ft_printf_fd(e->fd, "-->Verification de la fonction [%d]\n", func);
		free(free_me);
	}
	list.size = special_func(e, x, func, list.size);
	list.func = func;
	wait_time_downer(e, x, func);
	free(label);
	return (list);
}
