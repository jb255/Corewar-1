/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:50:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/28 15:08:57 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "function.h"
#include "g_variable.h"
#include "n_curse.h"

// 01 Registre, Suivie d’un octet (le numéro de registre)
// 10 Direct, Suivie de DIR_SIZE octets (la valeur directement)
// 11 Indirect, Suivie de IND_SIZE octets (la valeur de l’indirection)

// # define REG_CODE				1
// # define DIR_CODE				2
// # define IND_CODE				3

int				func_valid(t_env *e, t_type_func list, int func)
{
	ft_putstr_fd("Check de la fonction\n", e->fd);
	if (func == 2 && (!list.type[1].t_reg || (!list.type[0].t_ind && !list.type[0].t_dir) || list.type[0].t_reg))
		return (-1);
	if (func == 3 && (!list.type[0].t_reg || (!list.type[1].t_reg && !list.type[1].t_ind)))
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
}

t_type_func		find_label(t_env *e, int x)
{
	char		*label = NULL;
	char		*free_me = NULL;
	t_type_func	list;
	int			func;

	label = ft_sprintf("%02x", tab[e->process[x].position % MEM_SIZE]);
	func = instruct_tab_value(label);
	printf("Func %d\n", func);
	ft_putstr_fd(label, e->fd);
	ft_putnbr_fd(func, e->fd);
	func > 9 ? (func -= 1) : func;
	if ((func != 1 && func != 12 && func != -1) || label == NULL)
	{
		free_me = ft_sprintf("%02x", tab[(e->process[x].position + 1) % MEM_SIZE]);
		list = check_jump(e, hex_to_bin_quad(free_me));
		// check fonction a faire//
		if (func_valid(e, list, func) == -1)
			func = -1;
		free(free_me);
	}
	list.size = special_func(e, x, func, list.size);
	list.func = func;
	wait_time_downer(e, x, func);
	free(label);
	return (list);
}
