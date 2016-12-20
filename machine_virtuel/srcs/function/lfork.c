/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:29:51 by viko              #+#    #+#             */
/*   Updated: 2016/12/19 00:58:01 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

void	lfork_func(t_env *e, int xproc, t_type_func list)
{
	char		*new_start;
	int			position;
	int			value;

	new_start = get_x(e->process[xproc].position + 1,
		e->process[xproc].position + 3);
	value = (short)hex_to_dec(new_start);
	position = (e->process[xproc].position + value) % MEM_SIZE;
	set_process(e, e->active_process++, position, e->process[xproc].id_player);
	free(new_start);
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
}
