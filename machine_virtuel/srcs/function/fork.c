/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 04:26:17 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 15:26:43 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

// Pas d’octet de codage des paramètres, prend un index, opcode 0x0c
//  Crée un nouveau processus, qui hérite des différents états de son père,
//  à part son PC, qui est mis à (PC + (1er paramètre % IDX_MOD)).

int		check_fork(t_env *e, int xproc, t_type_func list)
{
	ft_printf_fd(e->fd, "Check_fork -- Fonction size %d\n", list.size);
	(void)xproc;
	(void)list;

	return (1);
}

void	fork_func(t_env *e, int xproc, t_type_func list)
{
	char		*new_start;
	int			position;

	new_start = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 3);
	position = e->process[xproc].position + ((short int)hex_to_dec(new_start) % IDX_MOD) - 1;
	position = position < 0 ? MEM_SIZE + position : position;
	// ft_printf_fd(e->fd, "-----Fork New Process at %d, Result[%d]\n", position, (short int)hex_to_dec(new_start) - 1);
	set_process(e, e->active_process++, position, e->process[xproc].id_player);
	free(new_start);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;

	nodelay(stdscr, 0);
	getch();

}
