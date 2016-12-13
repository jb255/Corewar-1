/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/13 18:57:52 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

int		name_process(t_env *e, char	*name)
{
	int		x;
	char	*tmp;

	tmp = NULL;
	x = 0;
	while (x < e->active_players)
	{
		if (!ft_strcmp(name, (tmp = ft_sprintf("%x", (e->players[x].id_live)))))
		{
			// ft_printf_fd(e->fd, "(`'-._ Live for %s _.-'`)\n", e->players[x].name);
			free(tmp);
			return (1);
		}
		x++;
		free(tmp);
	}
	return (0);
}

void	check_all_processlive(t_env *e)
{
	int		x;
	int		i;

	x = 0;
	while (x < e->active_process)
	{
		if (e->process[x].live_status == 0)
			i = 1;
		x++;
	}
	if (i)
		e->flag.cycle_to_die -= CYCLE_DELTA;
}

void	live_func(t_env *e, int xproc, t_type_func list)
{
	char		*result;

	(void)list;
	result = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 5);
	// if (name_process(e, result))
		e->process[xproc].live_status++;
	e->flag.live_call++;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
	free(result);
	if (e->flag.live_call == NBR_LIVE)
		check_all_processlive(e);
}
