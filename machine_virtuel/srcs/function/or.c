/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:38:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/15 16:38:35 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

void	or_func(t_env *e, int xproc, t_type_func list)
{
	int		i[4];
	int		error;
	int		place;

	place = 3;
	error = 0;
	i[0] = get_i02_func_and(list, e, xproc, &place); // VALUE du reg
	i[1] = get_i1_2_func_and(list, e, xproc, &place);
	i[2] = to_int_getx(get_x_from_position(e, e->process[xproc].position + place, e->process[xproc].position + (place + 1))); // Arg3
	i[3] = (i[0] | i[1]);
	if (place == -1)
		error = 1;
	if (!error)
		e->process[xproc].reg[i[2]] = i[3];
	if (i[3] && !error)
		e->process[xproc].carry = 0;
	else if (!error)
		e->process[xproc].carry = 1;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
