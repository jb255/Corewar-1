/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 02:00:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/14 15:04:03 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>
// sti : Opcode 11. Prend un registre, et deux index (potentiellement des registres).
// Additionne les deux derniers, utilise cette somme comme une adresse ou sera copiée la valeur du premier paramètre.

int		get_i02_func_sti(t_type_func list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	// ft_printf_fd(e->fd, "get_i02_func_sti ---- t_reg[%d]t_dir[%d]t_ind[%d]\n", list.type[0].t_reg, list.type[0].t_dir, list.type[0].t_ind);
	// ft_printf_fd(e->fd, "get_i02_func_sti ---- t_reg[%d]t_dir[%d]t_ind[%d]\n", list.type[1].t_reg, list.type[1].t_dir, list.type[1].t_ind);
	if (list.type[1].t_reg && (*place += 1))
		i = e->process[xproc].reg[reg_funcheck_and(e, xproc, *place)];
	else if (list.type[1].t_ind && (*place += 2))
		i = ind_funcheck_and(e, xproc, *place, list.type[1]);
	else if (list.type[1].t_dir && (*place += 2))
		i = ind_funcheck_and(e, xproc, *place, list.type[1]);
	return (i);
}

int		get_i1_2_func_sti(t_type_func list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	ft_printf_fd(e->fd, "get_i1_2_func_sti ---- t_reg[%d]t_dir[%d]t_ind[%d]\n", list.type[2].t_reg, list.type[2].t_dir, list.type[2].t_ind);
	if (list.type[2].t_reg && (*place += 1))
		i = e->process[xproc].reg[reg_funcheck_and(e, xproc, *place)];
	else if (list.type[2].t_dir && (*place += 2))
		i = ind_funcheck_and(e, xproc, *place, list.type[2]);
	return (i);
}

void	sti_func(t_env *e, int xproc, t_type_func list)
{
	int		i[4];
	int		place;
	int		error;

	error = 0;
	place = 3;
	(void)list;
	i[0] = to_int_getx(get_x_from_position(e, e->process[xproc].position + 2, e->process[xproc].position + 3)); // Valeur du reg
	i[1] = get_i02_func_sti(list, e, xproc, &place); // Valeur arg 1
	i[2] = get_i1_2_func_sti(list, e, xproc, &place); // Valeur arg 2
	ft_printf_fd(e->fd, "sti. Arg1[%d], Arg2[%d], Arg3[%d]\n", i[0], i[1], i[2]);
	i[3] = ((i[1]) + (i[2])) % IDX_MOD;
	if ((i[0] > 16 || i[0] < 1) || (list.type[1].t_reg && (i[1] > 16 || i[1] < 1)) || (list.type[2].t_reg && (i[2] > 16 || i[1] < 1)))
		error = 1;
	if (!error)
	{
		write_from_x(e, (e->process[xproc].position + i[3]), e->process[xproc].reg[i[0]], 4);
		write_from_tab2((e->process[xproc].position + i[3]), 4, e->process[xproc].id_player + 1);
	}
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
