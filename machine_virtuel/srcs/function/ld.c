/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:00:22 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 17:03:52 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

/*
** Cette instruction prend 2 paramètres, le deuxième est forcément un reg
** (pas le PC). Elle load la valeur du premier paramètre dans le registre.
** Cette opération modifie le carry.
** ld 34,r3 charge les REG_SIZE octets à partir de l’adresse =
** (PC + (34 % IDX_MOD)) dans le registre r3.
** {T_DIR | T_IND, T_REG},
*/

int		get_first_ld(t_env *e, t_type_func list, int *error, int xproc)
{
	int		result;

	result = 0;
	if (list.type[0].t_dir)
		result = to_int_getx(get_x(e->process[xproc].position + 2,
			e->process[xproc].position + 6));
	else if (list.type[0].t_ind)
		result = to_int_getx(get_x(e->process[xproc].position + 2,
			e->process[xproc].position + 4));
	else
		*error = 1;
	return (result);
}

void	set_carry_value(t_env *e, int xproc, int value, int reg)
{
	e->process[xproc].reg[reg] = value;
	if (value)
		e->process[xproc].carry = 0;
	else
		e->process[xproc].carry = 1;
}

void	ld_func(t_env *e, int xproc, t_type_func list)
{
	int			position;
	int			place;
	int			i[3];
	int			value;

	place = 0;
	i[0] = 0;
	i[1] = 0;
	i[2] = e->process[xproc].position;
	value = get_first_ld(e, list, &i[0], xproc);
	list.type[0].t_ind == 1 ? (place = 4) : place;
	list.type[0].t_dir == 1 ? (place = 6) : place;
	if (list.type[1].t_reg && !i[0])
		i[1] = to_int_getx(get_x(i[2] + place, i[2] + (place + 1)));
	(i[1] > 16 || i[1] < 1) ? (i[0] = 1) : i[0];
	if (list.type[0].t_ind && list.type[1].t_reg && !i[0])
	{
		position = i[2] + (value % IDX_MOD);
		value = to_int_getx(get_x(position, position + REG_SIZE));
	}
	if (!i[0])
		set_carry_value(e, xproc, value, i[1]);
	e->process[xproc].position = (i[2] + list.size) % MEM_SIZE;
}
