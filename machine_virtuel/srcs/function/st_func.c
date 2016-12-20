/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 04:07:26 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 16:40:09 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

/*
** • st : Prend un registre et un registre ou un indirect,
** et stocke la valeur du registre vers le second paramètre.
** 0x03. Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
** (PC + (42 % IDX_MOD))
** {T_REG, T_IND | T_REG}
*/

int		st_get(t_env *e, int xproc)
{
	int		reg;
	int		error;

	reg = to_int_getx(get_x(e->process[xproc].position + 3,
		e->process[xproc].position + 4));
	error = (reg > 16 || reg < 1) ? 1 : 0;
	if (!error)
	{
		reg = e->process[xproc].reg[reg];
		e->process[xproc].reg[reg] = reg;
	}
	return (0);
}

void	st_get_second(t_env *e, int xproc, int r1)
{
	int		reg;
	int		y;

	reg = (short)to_int_getx(get_x(e->process[xproc].position + 3,
		e->process[xproc].position + 5));
	y = (e->process[xproc].position + (reg % IDX_MOD)) % MEM_SIZE;
	write_from_x(e, y, e->process[xproc].reg[r1], 4);
	write_from_tab2(y, 4, e->process[xproc].id_player + 1);
}

void	st_func(t_env *e, int xproc, t_type_func list)
{
	int				reg;
	int				error;

	reg = 0;
	error = 0;
	if (list.type[0].t_reg)
		reg = to_int_getx(get_x(e->process[xproc].position + 2,
			e->process[xproc].position + 3));
	else
		error = 1;
	(reg > 16 || reg < 1) ? (error = 1) : error;
	if (list.type[1].t_reg && !error)
		error = st_get(e, xproc);
	else if (list.type[1].t_ind && !error)
		st_get_second(e, xproc, reg);
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
}
