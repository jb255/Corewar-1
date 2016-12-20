/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 04:26:17 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 01:51:55 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

/*
** Pas d’octet de codage des paramètres, prend un index, opcode 0x0c
** Crée un nouveau processus, qui hérite des différents états de son père,
** à part son PC, qui est mis à (PC + (1er paramètre % IDX_MOD)).
*/

void	fork_func(t_env *e, int xproc, t_type_func list)
{
	char		*new_start;
	int			position;
	int			value;

	new_start = get_x(e->process[xproc].position + 1,
		e->process[xproc].position + 3);
	value = (short)hex_to_dec(new_start) % IDX_MOD;
	position = (e->process[xproc].position + value) % MEM_SIZE;
	if (position < 0)
		position = MEM_SIZE + position;
	ft_printf_fd(e->fd, "P\t%d | fork %d\n", xproc, position);
	set_process(e, e->active_process++, position, e->process[xproc].id_player);
	free(new_start);
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
	if (e->active_process >= MAX_PROCESS)
	{
		if (e->flag.flag_n)
			endwin();
		ft_printf("Too much process for this VM.\n");
		exit(1);
	}
}
