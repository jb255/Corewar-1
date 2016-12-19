/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:31:30 by viko              #+#    #+#             */
/*   Updated: 2016/12/19 01:57:19 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

/*
** Comme ld sans le %IDX_MOD Cette opération modifie le carry.
*/

void	lld_func(t_env *e, int xproc, t_type_func list)
{
	int			reg;
	int			place;
	int			value;

	place = 0;
	reg = 0;
	value = get_first_ld(e, list, &place, xproc);
	list.type[0].t_ind == 1 ? (place = 4) : place;
	list.type[0].t_dir == 1 ? (place = 6) : place;
	if (list.type[1].t_reg && place >= 0)
		reg = to_int_getx(get_x(e, e->process[xproc].position +
			place, e->process[xproc].position + (place + 1)));
	(reg > 16 || reg < 1) ? (place = -1) : place;
	if (list.type[0].t_ind && list.type[1].t_reg && place >= 0)
		value = to_int_getx(get_x(e, e->process[xproc].position +
			(value), e->process[xproc].position + (value + REG_SIZE)));
	if (place >= 0)
		e->process[xproc].reg[reg] = value;
	if (value && place >= 0)
		e->process[xproc].carry = 0;
	else if (place >= 0)
		e->process[xproc].carry = 1;
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
}
