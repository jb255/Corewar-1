/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/17 03:33:03 by vlancien         ###   ########.fr       */
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
	// id = name_process(e, result);
	e->process[xproc].live_status++;
	// if (name_process(e, result))
	// {
	// 	ft_printf_fd(e->fd, "Process de /"RED"(`'-._ [%s]Live for %s _.-'`)"NORM"\n", result, e->players[e->arena.winner].name , e);
	// }
	// else{
	// 	ft_printf_fd(e->fd, "Process de /"RED"(`'-._ [%s]Live for %s _.-'`)"NORM"\n", result, "(unknow)");
	// }
	// e->arena.winner = xproc;
	e->arena.live_call++;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
	free(result);
}
