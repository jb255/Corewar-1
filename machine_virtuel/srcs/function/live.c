/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/15 16:16:24 by vlancien         ###   ########.fr       */
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
			free(tmp);
			return (x);
		}
		x++;
		free(tmp);
	}
	return (0);
}

// void	check_all_processlive(t_env *e)
// {
// 	int		x;
// 	int		i;
//
// 	x = e->active_process;
// 	while (x >= 0)
// 	{
// 		if (e->process[x].live_status == 0)
// 			i = 1;
// 		x--;
// 	}
// 	return (i);
// }

void	live_func(t_env *e, int xproc, t_type_func list)
{
	char		*result;
	int			id;

	id = 0;
	result = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 5);
	id = name_process(e, result);
	e->process[xproc].live_status++;
	if (id < e->active_players)
		ft_printf_fd(e->fd, ""RED"(`'-._ Live for %s _.-'`)"NORM"\n", e->players[id].name);
	else{
		ft_printf_fd(e->fd, ""RED"(`'-._ Live for %s[%d] _.-'`)"NORM"\n", "(unknow)", id);
		e->arena.winner = xproc;
	}
	e->flag.live_call++;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
	free(result);
}
