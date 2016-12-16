/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:39:34 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/15 23:08:46 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

// Cette opération modifie le carry.
// ldi 3,%4,r1 lit IND_SIZE octets a l’adresse : (PC + (3 % IDX_MOD)) ajoute 4 à cette valeur.
// On nommera S cette somme. On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD)) que l’on copie dans r1.
// Les paramètres 1 et 2 sont des index.
// T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG

int		get_ldi_arg(t_type_a list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	if (*place == -1)
		return (i);
	if (list.t_reg && (*place += 1))
	{
		i = reg_funcheck_and(e, xproc, *place);
		if (i > 16 || i < 1)
			*place = -1;
		i = e->process[xproc].reg[i];
		ft_printf_fd(e->fd , "Registre %d\n", i);
	}
	else if (list.t_ind && (*place += 2))
	{
		i = (short)to_int_getx(get_x_from_position(e, e->process[xproc].position + *place - 2, e->process[xproc].position + *place)) % IDX_MOD;
		ft_printf_fd(e->fd , "Indirect %d\n", i);
		i = to_int_getx(get_x_from_position(e, e->process[xproc].position + i, e->process[xproc].position + i + 4)) % IDX_MOD;
	}
	else if (list.t_dir && (*place += 2))
		i = (short)to_int_getx(get_x_from_position(e, e->process[xproc].position + *place - 2, e->process[xproc].position + *place)) % IDX_MOD;
	return (i);
}

void	ldi_func(t_env *e, int xproc, t_type_func list)
{
	int		i[5];
	int		place;
	int		error;

	error = 0;
	place = 2;
	ft_printf_fd(e->fd, "LDI\n");
	i[0] = get_ldi_arg(list.type[0], e, xproc, &place); // Arg 1
	i[1] = get_ldi_arg(list.type[1], e, xproc, &place); // Arg 2
	i[3] = to_int_getx(get_x_from_position(e, e->process[xproc].position + place, e->process[xproc].position + (place + 1))); // Arg3
	ft_printf_fd(e->fd, "{%d} {%d} {%d}\n", i[0], i[1], i[3]);
	i[2] = ((i[1] + i[0])); // Ajout de l'arg 2 a l'arg 1
	ft_printf_fd(e->fd, "Value ldi to search %d\n", i[2]);
	i[4] = to_int_getx(get_x_from_position(e, e->process[xproc].position + i[2], e->process[xproc].position + (i[2] + REG_SIZE)));
	if (place == -1)
		error = 1;
	if (!error)
		e->process[xproc].reg[i[3]] = i[4];
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
