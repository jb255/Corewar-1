/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player_in_memory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:55:52 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/29 14:31:58 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	player_to_tab(t_env *e, int x)
{
	int		byte = BYTE_START_CODE;
	int		start = e->players[x].start;
	char	*tmp = NULL;
	int		b;

	while (byte != (int)e->players[x].size)
	{
		tmp = print_hexa(e->players[x].file[byte], byte);
		b = (unsigned char)strtol(tmp, NULL, 16);
		tab[start] = b;
		tab2[start] = e->players[x].id_player + 1;
		// printf("%s, %d, %02x\n", tmp, x, x);
		byte++;
		start += 1;
		free(tmp);
	}
}

void	afficher(t_env *e)
{
	int			x;

	x = 0;
	while (x < e->active_process)
	{
		printf("Process .%d. = {%d}\n", x + 1, e->process[x].id_player);
		x++;
	}
}

void	get_position(t_env *e)
{
	int		saut;

	saut = MEM_SIZE / e->active_players;
	if (e->active_players >= 2)
		e->players[1].start = saut;
	if (e->active_players >= 3)
		e->players[2].start = saut * 2;
	if (e->active_players >= 4)
		e->players[3].start = saut * 3;

}

void	put_player(t_env *e)
{
	t_process	*list;
	int			x;

	x = -1;
	list = NULL;
	// e->process = malloc(sizeof(t_process*));
	get_position(e);
	e->active_process = e->active_players;
	while (++x < e->active_players)
	{
		init_process(e, x);
		e->players[x].position = e->players[x].start % MEM_SIZE;
		player_to_tab(e, x);
		e->process[x].position = e->players[x].position % MEM_SIZE;
		e->process[x].start = e->players[x].start % MEM_SIZE;
		e->process[x].id_player = e->players[x].id_player;
		e->process[x].reg[1] = -x - 1 ;
		ft_printf_fd(e->fd, "Processus %d, starting at : %d\n", x, e->process[x].start);
		e->process[x].char_player = 'F' - x;
		find_next_pc(e, x);
		// printf("New process %c,pos[%d] id player %d\n", e->process[x]->char_player, e->process[x].position, e->process[x].id_player);
	}
	// set_process(e, e->active_process++, (500), x);
	// set_process(e, e->active_process++, (501), x);
	// set_process(e, e->active_process++, (502), x);
	// set_process(e, e->active_process++, (503), x);
	// set_process(e, e->active_process++, (504), x);
	// set_process(e, e->active_process++, (506), x);
	// set_process(e, e->active_process++, (506), x);
	// set_process(e, e->active_process++, (507), x);
	// set_process(e, e->active_process++, (508), x);
	// set_process(e, e->active_process++, (509), x);
	// set_process(e, e->active_process++, (510), x);
	// set_process(e, e->active_process++, (520), x);
	// set_process(e, e->active_process++, (530), x);
	// set_process(e, e->active_process++, (540), x);
	// set_process(e, e->active_process++, (550), x);

	// afficher(e);
}
