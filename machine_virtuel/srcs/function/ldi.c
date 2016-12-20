/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:39:34 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 16:52:37 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

/*
** Cette opération modifie le carry.
** ldi 3,%4,r1 lit IND_SIZE octets a l’adresse : (PC + (3 % IDX_MOD))
** ajoute 4 à cette valeur.
** On nommera S cette somme. On lit REG_SIZE octet à l’adresse
** (PC + (S % IDX_MOD)) que l’on copie dans r1.
** Les paramètres 1 et 2 sont des index.
** T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG
*/

int		get_ldi_arg(t_type_a list, t_env *e, int xproc, int *p)
{
	int		i;
	int		pos;

	i = 0;
	pos = e->process[xproc].position;
	if (*p == -1)
		return (i);
	if (list.t_reg && (*p += 1))
	{
		i = reg_funcheck_and(e, xproc, *p);
		if (i > 16 || i < 1)
			*p = -1;
		else
			i = e->process[xproc].reg[i];
	}
	else if (list.t_ind && (*p += 2))
	{
		i = (short)to_int_getx(get_x(pos + *p - 2, pos + *p)) % IDX_MOD;
		i = to_int_getx(get_x(pos + i, pos + (i + 4))) % IDX_MOD;
	}
	else if (list.t_dir && (*p += 2))
		i = (short)to_int_getx(get_x(pos + *p - 2, pos + *p)) % IDX_MOD;
	return (i);
}

void	ldi_func(t_env *e, int xproc, t_type_func list)
{
	int		i[6];
	int		place;
	int		error;

	error = 0;
	place = 2;
	i[5] = e->process[xproc].position;
	if (list.type[2].t_ind || list.type[2].t_dir || list.type[1].t_ind)
	{
		error = 1;
		place = -1;
	}
	i[0] = get_ldi_arg(list.type[0], e, xproc, &place);
	i[1] = get_ldi_arg(list.type[1], e, xproc, &place);
	i[3] = to_int_getx(get_x(i[5] + place, i[5] + (place + 1)));
	if (i[3] > 16 || i[3] < 1 || place == -1)
		list.type[2].error = 1;
	i[2] = ((i[1] + i[0])) % MEM_SIZE;
	i[4] = to_int_getx(get_x(i[5] + i[2], i[5] + (i[2] + 4)));
	if (!list.type[0].error && !list.type[1].error && !list.type[2].error)
		e->process[xproc].reg[i[3]] = i[4];
	e->process[xproc].position = (i[5] + list.size) % MEM_SIZE;
}
