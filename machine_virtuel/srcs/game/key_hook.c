/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:20:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/14 20:07:17 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		key_hook(t_env *e)
{
	int		keycode;

	keycode = getch();
	if (keycode == 27)
		return (27);
	if (keycode == 43 && e->flag.time_cycle < 100000) // +
		e->flag.time_cycle += 1000;
	else if (keycode == 45 && e->flag.time_cycle == 2000) // -
		e->flag.time_cycle -= 1000;
	if (keycode == 32 && !e->flag.pause)
	{
		e->flag.pause = 1;
		display_info_menu(e);
	}
	else if (keycode == 32 && e->flag.pause == 1)
	{
		e->flag.pause = 0;
		display_info_menu(e);
	}
	if (keycode == 112) // p
		e->flag.obo = e->flag.obo == 1 ? 0 : 1;
	return (0);
}
