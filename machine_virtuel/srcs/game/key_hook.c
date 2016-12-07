/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:20:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/07 13:17:40 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		key_hook(t_env *e)
{
	int		keycode;

	(void)e;
	keycode = getch();
	// ft_printf_fd(e->fd, "Keycode %d\n", keycode);
	// if (keycode != -1)
		// vm_error("stop");
	if (keycode == 43 && e->flag.time_cycle < 100000) // +
		e->flag.time_cycle += 1000;
	else if (keycode == 45 && e->flag.time_cycle > 110) // -
	{
		e->flag.time_cycle -= 1000;
		e->process[0].position = 4000;
	}
	else if (keycode == 27)
		return (27);
	if (keycode == 32 && !e->flag.pause)
	{
		e->flag.pause = 1;
		wrefresh(e->window.menu);
	}
	else if (keycode == 32 && e->flag.pause == 1)
	{
		e->flag.pause = 0;
		return (1);
	}
	if (keycode == 112)
		e->flag.obo = e->flag.obo == 1 ? 0 : 1;
	return (0);
}
