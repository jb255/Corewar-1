/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player_in_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:55:52 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 04:57:11 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	player_to_tab(t_env *e, int x)
{
	int		byte = BYTE_START_CODE;
	int		start = e->players[x].start;
	char	*tmp = NULL;

	while (byte < (int)e->players[x].size)
	{
		// tmp = print_hexa(e->players[x].file[byte], byte);
		// // printf("%02x\n", e->players[x].file[byte]);
		// e->players[x].file[byte]
		// tab[start % ((MEM_SIZE))] = tmp[0];
		// tab[(start + 1) % ((MEM_SIZE))] = tmp[1];
		// tab2[start % ((MEM_SIZE))] = x + 1;
		// tab2[(start + 1) % ((MEM_SIZE))] = x + 1;
		tmp = print_hexa(e->players[x].file[byte], byte);


		// memcpy(tmp[start], ft_strjoin("\x", tmp), 1);
		int x = (unsigned char)strtol(tmp, NULL, 16);
		tab[start] = x;
		tab2[start] = (unsigned char)e->players[x].id_player + 1;
		printf("%s, %d, %02x\n", tmp, x, x);

		byte++;
		start += 1;
		free(tmp);
	}
	// exit(0);
}

void	afficher(t_env *e)
{
	int			x;

	x = 0;
	while (x < e->active_process)
	{
		printf("Process .%d. = {%d}\n", x + 1, e->process[x]->id_player);
		x++;
	}
}

void	put_player(t_env *e)
{
	t_process	*list;
	int			x;

	x = -1;
	list = NULL;
	e->process = malloc(sizeof(t_process*));
	e->active_process = e->active_players;
	while (++x < e->active_players)
	{
		init_process(e, x);
		e->players[x].position = e->players[x].start % ((MEM_SIZE));
		player_to_tab(e, x);
		e->process[x]->position = e->players[x].position % ((MEM_SIZE));
		e->process[x]->start = e->players[x].start % ((MEM_SIZE));
		e->process[x]->id_player = e->players[x].id_player + 1;
		e->process[x]->char_player = 'F' - x;
		// find_next_pc(e, x);
		printf("New process %c, id player %d\n", e->process[x]->char_player, e->process[x]->id_player);
	}
	// set_process(e, e->active_process++, 2500, x - 1);
	afficher(e);
}
