/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:20:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 04:41:27 by vlancien         ###   ########.fr       */
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
	if (keycode == 43 && e->arena.time_cycle == 1 && (done = 1))
		e->arena.time_cycle = 0;
	else if (keycode == 45 && e->arena.time_cycle == 0 && (done = 1))
		e->arena.time_cycle = 1;
	if (keycode == 32 && (done = 1))
		e->flag.pause = e->flag.pause == 1 ? 0 : 1;
	if (keycode == 112 && (done = 1))
		e->flag.obo = e->flag.obo == 1 ? 0 : 1;
	if (done)
		display_info_menu(e);
	return (keycode);
}
