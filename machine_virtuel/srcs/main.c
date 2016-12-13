/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:59:13 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/13 19:16:09 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <n_curse.h>
#include <players.h>

void	free_fighter(t_env *e)
{
	int		x;

	x = 0;
	while (x < e->active_players)
	{
		free(e->players[x].name);
		free(e->players[x].file);
		free(e->players[x].comment);
		x++;
	}
}

void	display_memoryspeed(t_env *e)
{
	init_index(&e->memory_data[2], &e->memory_data[0], &e->memory_data[1]);
	while (!memory_run(e))
	{
		e->arena.cycle--;
		if (e->arena.cycle == 1000)
			break;
	}
}

int		main(int argc, char **argv)
{
	t_env *e;

	e = (t_env *)ft_memalloc(sizeof(t_env));
	if (argc < 2)
		vm_error("Need more argument!");
	e->fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	op_tab(e);
	ft_printf_fd(e->fd, "%080s%d\n\n\n\n", ".NEW LAUNCH.", 111607808 % MEM_SIZE );

	e->flag.live_call = 0;
	e->flag.cycle_to_die = CYCLE_TO_DIE;
	parsing_arg(argv, e);
	init_curse();
	put_player(e);
	e->arena.cycle = 0;
	e->flag.pause = 0;
	if (e->flag.flag_n)
		n_curse(e);
	else
		display_memoryspeed(e);
	free_fighter(e);
	return (0);
}
