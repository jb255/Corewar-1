/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 03:20:45 by vlancien         ###   ########.fr       */
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
		if (!ft_strcmp(name, dec_to_hex(-(e->players[x].id_player+1), NULL, 3)))
			printf("LIVE FOR %s\n", e->players[x].name);
		x++;
	}
}

char	*get_x_from_position(t_env *e, int xproc, int at)
{
	char			*result = "";
	unsigned int	x;
	char			*name;
	int				index;

	index = 1;
	while (index < at)
	{
		x = tab[e->process[xproc]->position + index];
		name = strdup(dec_to_hex(x, NULL, intlen(x, 10)));
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
	result = get_x_from_position(e, xproc, 5);
	name_process(e, result);
	free(result);
	nodelay(stdscr, 1);
	getch();
}
