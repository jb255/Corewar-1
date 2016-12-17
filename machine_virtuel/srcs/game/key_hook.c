/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:20:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/16 17:54:24 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		key_hook(t_env *e)
{
	int		keycode;
	int		done;

	done = 0;
	keycode = getch();
	if (keycode == 27)
	{
		if (e->flag.flag_n)
		{
			endwin();
			exit(1);
		}
		return (27);
	}
	if (keycode == 43 && e->arena.time_cycle < 4 && (done = 1)) // +
		e->arena.time_cycle += 1;
	else if (keycode == 45 && e->arena.time_cycle > 1 && (done = 1)) // -
		e->arena.time_cycle -= 1;
	if (keycode == 32 && (done = 1)) // Enter
		e->flag.pause = e->flag.pause == 1 ? 0 : 1;
	if (keycode == 112 && (done = 1)) // p
		e->flag.obo = e->flag.obo == 1 ? 0 : 1;
	if (done)
		display_info_menu(e);
	return (keycode);
}
