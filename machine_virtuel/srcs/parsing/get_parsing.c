/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 16:57:39 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 16:58:54 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		id_exist(t_env *e, int id, int xbis)
{
	int		x;

	x = 0;
	while (x < e->active_players)
	{
		if (e->players[x].id_live == id && x != xbis)
			return (1);
		x++;
	}
	return (0);
}

void	get_idprog(t_env *e)
{
	int		x;
	int		itg;

	itg = -1;
	x = 0;
	while (x < e->active_players)
	{
		if (e->players[x].id_live == 0)
		{
			while (id_exist(e, itg, x))
				itg--;
			e->players[x].id_live = itg;
		}
		x++;
	}
}

int		ft_isid(char *str)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
	{
		if ((str[index] == '-' || str[index] == '+') && index == 0)
			index++;
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}
