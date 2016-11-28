/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/28 15:18:56 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	name_process(t_env *e, char	*name)
{
	int		x;
	char	*tmp;

	tmp = NULL;
	x = 0;
	while (x < e->active_players)
	{
		if (!ft_strcmp(name, (tmp = ft_sprintf("%x", (e->players[x].id_player-1)))))
			printf("LIVE FOR %s\n", e->players[x].name);
		x++;
		free(tmp);
	}
}

char	*get_x_from_position(t_env *e, int xproc, int from, int at)
{
	char			*result = "";
	char			*name;
	int				index;

	(void)xproc;
	index = from;
	while (index < at)
	{
		ft_printf_fd(e->fd, "---------->Recherche a partir de %d a %d ->Actual n%d[%d] hex[%02x]\n", from, at, index,tab[index % MEM_SIZE], tab[index % MEM_SIZE]);
		name = ft_sprintf("%02x", tab[index % MEM_SIZE]);
		result = ft_strjoin(result, name);
		index++;
		free(name);
	}
	return (result);
}

// char	*get_x_from_x(t_env *e, int xproc, int from, int at)
// {
// 	char			*result = "";
// 	char			*name;
// 	int				index;
//
// 	index = from;
// 	while (index < at)
// 	{
// 		name = ft_sprintf("%X", tab[index]);
// 		result = ft_strjoin(result, name);
// 		index++;
// 		free(name);
// 	}
// 	return (result);
// }

void	live_func(t_env *e, int xproc, t_type_func list)
{
	char		*result;

	(void)list;
	result = get_x_from_position(e, xproc, e->process[xproc].position + 1, e->process[xproc].position + 5);
	name_process(e, result);
	free(result);
	nodelay(stdscr, 1);
	getch();
}
