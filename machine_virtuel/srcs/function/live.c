/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/18 19:44:02 by vlancien         ###   ########.fr       */
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
			e->arena.winner = x;
			if (!e->flag.flag_n)
				ft_printf("un processus dit que le joueur %d(%s) est en vie\n", e->players[e->arena.winner].id_live, e->players[e->arena.winner].name);
			// if (e->flag.log)

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
	// int			id;

	// id = 0;
	result = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 5);

	name_process(e, result);
	e->process[xproc].live_status++;
	ft_printf_fd(e->fd, "Process de %d/"RED"(`'-._ Live for %s _.-'`)"NORM"\n", xproc, e->players[e->arena.winner].name);
	e->arena.live_call++;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
	free(result);
}
