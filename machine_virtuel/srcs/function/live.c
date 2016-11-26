/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 06:44:41 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	name_process(t_env *e, char	*name)
{
	int		x;

	x = 0;
	while (x < e->active_players)
	{

		if (!ft_strcmp(name, ft_sprintf("%X", (e->players[x].id_player-1))))
			printf("LIVE FOR %s\n", e->players[x].name);
		x++;
	}
}

char	*get_x_from_position(t_env *e, int xproc, int from, int at)
{
	char			*result = "";
	char			*name;
	int				index;

	index = from;
	while (index < at)
	{
		name = strdup(ft_sprintf("%X", tab[e->process[xproc].position + index]));
		result = ft_strjoin(result, name);
		index++;
		free(name);
	}
	return (result);
}

void	live_func(t_env *e, int xproc, t_type_func list)
{
	char		*result;

	(void)list;
	result = get_x_from_position(e, xproc, 1, 5);
	name_process(e, result);
	free(result);
	nodelay(stdscr, 1);
	getch();
}
