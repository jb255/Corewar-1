/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_fight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:16:37 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/13 12:45:36 by vlancien         ###   ########.fr       */
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
	while (x < e->active_process)
	{
		if (key_hook(e) == 27)
			return (1);
		list = find_label(e, x);
		// ft_printf_fd(e->fd, "List func = %d\n", list.func);
		if (list.func == -1)
			e->process[x].position = (e->process[x].position + 1) % MEM_SIZE;
		else if (e->process[x].wait_time - 1 <= 0)
		{
			if (list.func != -1){
				apply_func(e, x, list);
				nodelay(stdscr, 0);
				getch();
			}
			e->process[x].wait_time = 0;
		}
		x++;
	}
	// 2 = addr
	// 0 = y
	// 1 = x
	// 3 = nb_proces
	return (0);
}
