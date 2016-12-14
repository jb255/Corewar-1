/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:31:30 by viko              #+#    #+#             */
/*   Updated: 2016/12/14 21:34:04 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// Comme ld sans le %IDX_MOD Cette opération modifie le carry.

void	lld_func(t_env *e, int xproc, t_type_func list)
{
	int			position;
	int			reg;
	int			place;
	int			error;
	int			value;

	place = 0;
	reg = 0;
	error = 0;
	value = get_first_ld(e, list, &error, xproc);
	list.type[0].t_ind == 1 ? (place = 4) : place;
	list.type[0].t_dir == 1 ? (place = 6) : place;
	if (list.type[1].t_reg && !error)
		reg = to_int_getx(get_x_from_position(e, e->process[xproc].position + place, e->process[xproc].position + (place + 1)));
	(reg > 16 || reg < 1) ? (error = 1) : error;
	if (list.type[0].t_ind && list.type[1].t_reg && !error)
	{
		position = e->process[xproc].position + (value);
		value = to_int_getx(get_x_from_position(e, position, position + REG_SIZE));
	}
	if (!error)
		e->process[xproc].reg[reg] = value;
	if (value && !error)
		e->process[xproc].carry = 0;
	else if (!error)
		e->process[xproc].carry = 1;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
