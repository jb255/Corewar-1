/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:21 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/16 23:35:40 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// Cette instruction prend 3 registres en paramètre,
// additionne le contenu des 2 premiers et met le résultat dans le troisième.
// Cette opération modifie le carry.
// add r2,r3,r5 additionne r2 et r3 et met le résultat dans r5
// {T_REG, T_REG, T_REG},
void	add_func(t_env *e, int xproc, t_type_func list)
{
	int		i[3];
	int		error;

	error = 0;
	i[0] = to_int_getx(get_x_from_position(e, e->process[xproc].position + 2, e->process[xproc].position + 3));
	i[1] = to_int_getx(get_x_from_position(e, e->process[xproc].position + 3, e->process[xproc].position + 4));
	i[2] = to_int_getx(get_x_from_position(e, e->process[xproc].position + 4, e->process[xproc].position + 5));
	// ft_printf_fd(e->fd, "Arg1[%d] // Arg2[%d] // Arg3[%d]", i[0], i[1], i[2]);
	if ((i[0] > 16 || i[0] < 1) || (i[1] > 16 || i[1] < 1) || (i[2] > 16 || i[2] < 1))
		error = 1;
	if (list.type[0].t_reg && list.type[1].t_reg && list.type[2].t_reg && !error)
	{
		e->process[xproc].reg[i[2]] =
		e->process[xproc].reg[i[0]] +
		e->process[xproc].reg[i[1]];
	}
	if (i[2] && !error)
		e->process[xproc].carry = 0;
	else if (!error)
		e->process[xproc].carry = 1;
	// ft_printf_fd(e->fd, "--->Function add\n--->Registre[%s] %d update:  [%d]\n", regist[2], hex_to_dec(regist[2]), e->process[xproc].reg[hex_to_dec(regist[2])]);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
