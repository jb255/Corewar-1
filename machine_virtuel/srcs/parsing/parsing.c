/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:57:55 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/06 16:20:19 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_cor(char *str)
{
	int		index;

	index = ft_strlen(str);
	if (index < 4)
		vm_error("File error. Need *.cor !");
	if (strstr(str, ".cor\0"))
		return (1);
	return (0);
}

void	flag(char *str, t_env *e)
{
	int		index;

	index = 0;
	if (str[1] == 'c' && str[2] == '\0')
		e->flag.flag_n = 1;
	else if (str[1] == 'd' && str[2] == 'u' && str[3] == 'm' && str[4] == 'p' && str[5] == '\0')
	{
		if (e->flag.flag_dump == 1)
			vm_error("Too much -dump");
		e->flag.flag_dump = 1;
	}
	else if (str[1] == 'n' && str[2] == '\0')
		e->flag.flag_number = 1;
}

void	get_flag_prog(char *arg, t_env *e)
{
	if (e->flag.flag_dump == 1)
	{
		e->flag.dump = ft_atoi(arg);
		e->flag.flag_dump = 2;
	}
	else if (e->flag.flag_number == 1)
	{
		e->players[e->active_players].id_player = ft_atoi(arg);
		e->flag.flag_number = 0;
	}
	else if (arg[0] == '-')
	{
		flag(arg, e);
		printf(""RED"%s\n"NORM"", arg);
	}
	else if (e->active_players != MAX_PLAYERS && is_cor(arg))
	{
		e->players[e->active_players].path = arg;
		e->active_players++;
	}
	else if (e->active_players == MAX_PLAYERS)
		vm_error("Too much champions!");
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
	int x = 0;
	while (x < e->active_players)
	{
		printf("Champion %d: %s\n",x + 1, e->players[x].path);
		reading_file(e, x);
		printf("ID %d\nPlayer name: %s\n", e->players[x].id_player, e->players[x].name);
		printf("Player comment: %s\n", e->players[x].comment);
		e->players[x].id_player = x;
		size_total += e->players[x].size_func;
		x++;
		printf("\n");
	}
	if ((MEM_SIZE) < size_total)
		vm_error("Not enough space available.");
	return ;
}
