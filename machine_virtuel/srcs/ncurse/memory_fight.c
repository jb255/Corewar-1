/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:16:37 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 17:45:46 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

extern char	g_status_code[17][8];

// void	exec_process(t_env *e, int xproc)
// {
	// char		*label;
	// t_type_func	list;
	// int			func;
	// char		*free_me;
	//
	// label = to_tab(ft_itoa_base(tab[e->process[xproc].position], 16));
	// func = instruct_tab_value(label);
	// if (func > 9)
	// 	func--;
	// printf("FUNC %d\n", func);
	// free_me = to_tab(ft_itoa_base(tab[(e->process[xproc].position + 1) % MEM_SIZE], 16));
	// list = check_jump(e, hex_to_bin_quad(free_me));
	// free(free_me);
// }

int		memory_run(t_env *e)
{
	int				x;
	t_type_func		list;

	x = 0;
	e->memory_data[3] = 0;
	while (x < e->active_process)
	{
		if (key_hook(e) == 27)
			return (1);
		// ft_printf_fd(e->fd, "[%d]Execution du process pour le joueur %d\n", x, e->process[x].id_player);
		list = find_label(e, x);
		// ft_printf_fd(e->fd, "List func = %d\n", list.func);
		if (list.func == -1)
			e->process[x].position = (e->process[x].position + 1) % MEM_SIZE;
		else if (e->process[x].wait_time - 1 <= 0)
		{
			// ft_printf_fd(e->fd, "[%d] Application de la fonction ?\n", x);
			if (list.func != -1){
				// ft_printf_fd(e->fd, "Enter function %d\n", list.func);
				apply_func(e, x, list);
				// ft_printf_fd(e->fd, "	Exit function %d\n", list.func);
			}
			e->process[x].wait_time = 0;
		}
		// ft_printf_fd(e->fd, "Le processus %d est a %d\n", x, e->process[x].position);
		x++;
	}
	// delete_process(e, 0);
	// 2 = addr
	// 0 = y
	// 1 = x
	// 3 = nb_proces
	return (0);
}
