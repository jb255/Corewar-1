/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:21 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 16:22:30 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

/*
** Cette instruction prend 3 registres en paramètre,
** additionne le contenu des 2 premiers et met le résultat dans le troisième.
** Cette opération modifie le carry.
** add r2,r3,r5 additionne r2 et r3 et met le résultat dans r5
** {T_REG, T_REG, T_REG},
*/

void	add_func(t_env *e, int xproc, t_type_func list)
{
	int		i[5];

	i[3] = 0;
	i[4] = e->process[xproc].position;
	if (list.type[0].t_ind || list.type[0].t_dir || list.type[1].t_ind ||
		list.type[1].t_dir || list.type[2].t_ind || list.type[2].t_dir)
		i[3] = 1;
	i[0] = to_int_getx(get_x(i[4] + 2, i[4] + 3));
	i[1] = to_int_getx(get_x(i[4] + 3, i[4] + 4));
	i[2] = to_int_getx(get_x(i[4] + 4, i[4] + 5));
	if ((i[0] > 16 || i[0] < 1) || (i[1] > 16 || i[1] < 1) ||
	(i[2] > 16 || i[2] < 1))
		i[3] = 1;
	if (list.type[0].t_reg && list.type[1].t_reg && list.type[2].t_reg && !i[3])
	{
		e->process[xproc].reg[i[2]] =
		e->process[xproc].reg[i[0]] +
		e->process[xproc].reg[i[1]];
	}
	if (i[2] && !i[3])
		e->process[xproc].carry = 0;
	else if (!i[3])
		e->process[xproc].carry = 1;
	e->process[xproc].position = (i[4] + list.size) % MEM_SIZE;
}
