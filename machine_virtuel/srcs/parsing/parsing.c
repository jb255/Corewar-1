/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:57:55 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 17:44:22 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_cor(char *str)
{
	int		index;

	index = ft_strlen(str);
	if (index < 4)
		vm_error("File error. Need *.cor !");
	str = str + index - 4;
	if (!ft_strcmp(".cor", str))
		return (1);
	vm_error("File error. Need *.cor !");
	return (0);
}

void	flag(char *str, t_env *e)
{
	int		index;

	index = 0;
	if (str[1] == 'c' && str[2] == '\0')
		e->flag.flag_n = 1;
	else if (!ft_strcmp(str, "-dump"))
	{
		if (e->flag.flag_dump == 1)
			vm_error("Too much -dump");
		e->flag.flag_dump = 1;
	}
	else if (str[1] == 'n' && str[2] == '\0')
		e->flag.flag_number = 1;
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

void	get_flag_prog(char *arg, t_env *e)
{
	if (e->flag.flag_dump == 1)
	{
		if (!ft_isid(arg))
			vm_error("-dump error");
		e->flag.dump = ft_atoi(arg);
		e->flag.flag_dump = 0;
	}
	else if (e->flag.flag_number == 1)
	{
		if (!ft_isid(arg) && ft_atoi(arg) != 0)
			vm_error("-n error");
		e->players[e->active_players].id_live = ft_atoi(arg);
		e->flag.flag_number = 0;
	}
	else if (arg[0] == '-')
		flag(arg, e);
	else if (e->active_players != MAX_PLAYERS && is_cor(arg))
	{
		e->players[e->active_players].path = arg;
		e->active_players++;
	}
	else if (e->active_players == MAX_PLAYERS)
		vm_error("Too much champions!");
}

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

void	parsing_arg(char **arg, t_env *e)
{
	int		i;
	int		size_total = 0;

	i = 1;
	while (arg[i])
	{
		get_flag_prog(arg[i], e);
		i++;
	}
	get_idprog(e);
	int x;
	x = 0;
	ft_printf("Introducing all players...\n");
	if (!e->active_players)
		vm_error("No player");
	while (x < e->active_players)
	{
		reading_file(e, x);
		ft_printf("* Player %d, weighing %d bytes,", x + 1, e->players[x].size - BYTE_START_CODE);
		ft_printf(" \"%s\" (\"%s\") !\n",e->players[x].name, e->players[x].comment);
		e->players[x].id_player = x;
		size_total += e->players[x].size_func;
		x++;
	}
	if ((MEM_SIZE) < size_total)
		vm_error("Not enough space available.");
	return ;
}
