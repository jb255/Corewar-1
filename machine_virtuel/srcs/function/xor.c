/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:40:11 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 02:11:24 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		get_xorandor_arg(t_type_a list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	if (*place == -1)
		return (i);
	if (list.t_reg && (*place += 1))
	{
		i = reg_funcheck_and(e, xproc, *place);
		if (i > 16 || i < 1)
			list.error = 1;
		i = e->process[xproc].reg[i];
	}
	else if (list.t_ind && (*place += 2))
	{
		i = (short)to_int_getx(get_x(e, e->process[xproc].position + *place - 2,
			e->process[xproc].position + *place)) % IDX_MOD;
		i = to_int_getx(get_x(e, e->process[xproc].position + i,
			e->process[xproc].position + i + 4));
	}
	else if (list.t_dir && (*place += 4))
		i = to_int_getx(get_x(e, e->process[xproc].position + *place - 4,
			e->process[xproc].position + *place));
	return (i);
}

void	xor_func(t_env *e, int xproc, t_type_func list)
{
	int		i[4];
	int		place;
	int		error;

	error = 0;
	place = 2;
	if (list.type[2].t_ind || list.type[2].t_dir)
		error = 1;
	i[0] = get_xorandor_arg(list.type[0], e, xproc, &place);
	i[1] = get_xorandor_arg(list.type[1], e, xproc, &place);
	i[2] = to_int_getx(get_x(e, e->process[xproc].position + place,
		e->process[xproc].position + (place + 1)));
	(i[2] > 16 || i[2] < 1) ? (error = 1) : error;
	i[3] = (i[0] ^ i[1]);
	if (place == -1)
		error = 1;
	if (!error)
		e->process[xproc].reg[i[2]] = i[3];
	if (i[3] && !error)
		e->process[xproc].carry = 0;
	else if (!error)
		e->process[xproc].carry = 1;
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
}
