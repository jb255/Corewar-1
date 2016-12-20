/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 16:22:30 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

int		name_process(t_env *e, char *name)
{
	int		x;
	char	*tmp;

	tmp = NULL;
	x = 0;
	while (x < e->active_players)
	{
		if (!ft_strcmp(name,
			(tmp = ft_sprintf("%08x", (e->players[x].id_live)))))
		{
			e->arena.winner = x;
			if (!e->flag.flag_n)
				ft_printf("un processus dit que le joueur %d(%s) est en vie\n",
		e->players[e->arena.winner].id_live, e->players[e->arena.winner].name);
			ft_printf_fd(e->fd, ""RED"(`'-._ Live for %s_.-'`)"NORM"\n",
			e->players[e->arena.winner].name);
			free(tmp);
			return (1);
		}
		x++;
		free(tmp);
	}
	return (0);
}

void	live_func(t_env *e, int xproc, t_type_func list)
{
	char		*result;

	result = get_x(e->process[xproc].position + 1,
		e->process[xproc].position + 5);
	name_process(e, result);
	e->process[xproc].live_status++;
	e->arena.live_call++;
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
	free(result);
}
