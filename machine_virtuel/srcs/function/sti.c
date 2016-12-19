/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 02:00:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 21:32:55 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>
/*
** sti : Opcode 11. Prend un registre, et deux index (potentiellement des registres).
** Additionne les deux derniers, utilise cette somme comme une adresse ou sera copiée la valeur du premier paramètre.
** {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
*/

int		get_i02_func_sti(t_type_func list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	if (list.type[1].t_reg && (*place += 1))
	{
		i = reg_funcheck_and(e, xproc, *place);
		ft_printf_fd(e->fd, " r%d", i);
		if (i > 16 || i < 1)
			*place = -1;
		i = e->process[xproc].reg[i];
	}
	else if (list.type[1].t_ind && (*place += 2))
	{
		i = (short)to_int_getx(get_x(e, e->process[xproc].position + *place - 2, e->process[xproc].position + *place)) % IDX_MOD;
		ft_printf_fd(e->fd, " %d->%s", i, get_x(e, e->process[xproc].position + *place - 2, e->process[xproc].position + *place));
		i = (short)to_int_getx(get_x(e, e->process[xproc].position + i, e->process[xproc].position + i + 2));
		ft_printf_fd(e->fd, " {%d}", i);

	}
	else if (list.type[1].t_dir && (*place += 2)){
		i = (short)to_int_getx(get_x(e, e->process[xproc].position + *place - 2, e->process[xproc].position + *place)) % IDX_MOD;
		ft_printf_fd(e->fd, " %d", i);

	}
	return (i);
}

int		get_i1_2_func_sti(t_type_func list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	if (*place == -1)
		return (i);
	if (list.type[2].t_reg && (*place += 1))
	{
		i = reg_funcheck_and(e, xproc, *place);
		ft_printf_fd(e->fd, " r%d\n", i);
		if (i > 16 || i < 1)
			*place = -1;
		i = e->process[xproc].reg[i];
	}
	else if (list.type[2].t_dir && (*place += 2))
		i = (short)to_int_getx(get_x(e, e->process[xproc].position + *place - 2, e->process[xproc].position + *place)) % IDX_MOD;
	return (i);
}

void	sti_func(t_env *e, int xproc, t_type_func list)
{
	int		i[4];
	int		place;
	int		error;

	error = 0;
	place = 3;
	i[0] = to_int_getx(get_x(e, e->process[xproc].position + 2, e->process[xproc].position + 3));
	ft_printf_fd(e->fd, "Sti\nr%d ", i[0]);
	// ft_printf_fd(e->fd, "P\t%d | sti r%s", xproc, get_x(e, e->process[xproc].position + 2, e->process[xproc].position + 3));
	i[1] = get_i02_func_sti(list, e, xproc, &place);
	i[2] = get_i1_2_func_sti(list, e, xproc, &place);
	i[3] = ((i[1]) + (i[2])) % IDX_MOD;
	if (place == -1)
		error = 1;
	if (!error)
	{
		write_from_x(e, (e->process[xproc].position + i[3]), e->process[xproc].reg[i[0]], 4);
		write_from_tab2((e->process[xproc].position + i[3]), 4, e->process[xproc].id_player + 1);
	}
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
