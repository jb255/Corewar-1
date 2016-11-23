/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:20:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/23 08:52:01 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		key_hook(t_env *e)
{
	int		keycode;

	(void)e;
	keycode = getch();
	// printf("keycode %d\n", keycode);
	if (keycode == 43 && e->flag.time_cycle < 100000) // +
		e->flag.time_cycle += 1000;
	else if (keycode == 45 && e->flag.time_cycle > 110) // -
		{
			e->flag.time_cycle -= 1000;
			e->process[0]->position = 4000;
		}
	else if (keycode == 27)
		return (27);
	if (keycode == 32 && !e->flag.pause) {
		e->flag.pause = 1;
		// wrefresh(e->window.memory);
		wrefresh(e->window.menu);
	}
	else if (keycode == 32 && e->flag.pause == 1) {
		e->flag.pause = 0;
		return (1);
	}
	// if (keycode != -1)
	// 	wrefresh(e->window.menu);
	return (0);
}
