/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:16:37 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/16 01:22:22 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

extern char	g_status_code[17][8];

int		memory_run(t_env *e)
{
	int				x;
	t_type_func		list;

	x = 0;
	e->memory_data[3] = 0;
	x = e->active_process - 1;
	while (x >= 0)
	{

		nodelay(stdscr, e->flag.obo == 1 ? 0 : 1);
		list = find_label(e, x);
		if (e->process[x].wait_time - 1 <= 0)
		{
			if (key_hook(e) == 27)
				return (1);
			if (list.func != -1 && !list.error){
				apply_func(e, x, list);
			}
			if (list.func == -1 || list.error)
				e->process[x].position = (e->process[x].position + 1) % MEM_SIZE;
			e->process[x].wait_time = 0;
		}
		x--;
	}
	// 2 = addr
	// 0 = y
	// 1 = x
	// 3 = nb_proces
	return (0);
}
