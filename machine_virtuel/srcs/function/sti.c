/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 02:00:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/03 04:19:01 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>
// sti : Opcode 11. Prend un registre, et deux index (potentiellement des registres).
// Additionne les deux derniers, utilise cette somme comme une adresse ou sera copiée la valeur du premier paramètre.

int		check_sti(t_env *e, int xproc, t_type_func list)
{
	ft_printf_fd(e->fd, "Check_sti -- Fonction size %d\n", list.size);
	(void)xproc;
	(void)list;

	return (1);
}

int		get_i02_func_sti(t_type_func list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	ft_printf_fd(e->fd, "get_i02_func_sti ---- t_reg[%d]t_dir[%d]t_ind[%d]\n", list.type[1].t_reg, list.type[1].t_dir, list.type[1].t_ind);
	if (list.type[1].t_reg && (*place += 1))
		i = reg_funcheck_and(e, xproc, *place);
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
		i = reg_funcheck_and(e, xproc, *place);
	else if (list.type[2].t_dir && (*place += 2))
		i = ind_funcheck_and(e, xproc, *place, list.type[2]);
	return (i);
}

void	sti_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist[2];
	int		i[4];
	int		place;
	int		error;

	error = 0;
	place = 3;
	(void)list;
	(void)i;
	ft_printf_fd(e->fd, "Check_sti -- \n");
	regist[0] = get_x_from_position(e, e->process[xproc].position + 2, e->process[xproc].position + 3);
	i[0] = hex_to_dec(regist[0]);
	ft_printf_fd(e->fd, "Check_sti -- Registre[%s]\n", regist[0]);
	if (i[0] > 16 || i[0] < 1)
		error = 1;
	else
		i[0] = e->process[xproc].reg[i[0]];
	i[1] = get_i02_func_sti(list, e, xproc, &place);
	ft_printf_fd(e->fd, "Check_sti -- Data 1 [%d]\n", i[1]);
	if (list.type[1].t_reg && (i[1] > 16 || i[1] < 1))
		error = 1;
	else if (list.type[1].t_reg)
		i[1] = e->process[xproc].reg[i[1]];
	ft_printf_fd(e->fd, "Check_sti -- Data 1 value [%d]\n", i[1]);
	i[2] = get_i1_2_func_sti(list, e, xproc, &place);
	ft_printf_fd(e->fd, "Check_sti -- Data 2 [%d]\n", i[2]);
	if (list.type[2].t_reg && (i[2] > 16 || i[1] < 1))
		error = 1;
	else if (list.type[2].t_reg)
		i[2] = e->process[xproc].reg[i[2]];
	ft_printf_fd(e->fd, "Check_sti -- Data 2 value [%d]\n", i[2]);
	i[3] = i[1] + i[2];
	ft_printf_fd(e->fd, "Check_sti -- Regist[%d] - Address [%d] to write [%x] -- error %d\n", hex_to_dec(regist[0]),i[3], e->process[xproc].reg[hex_to_dec(regist[0])],error);
	if (!error)
	{
		write_from_x(e, (e->process[xproc].position + (i[3] % (IDX_MOD))), e->process[xproc].reg[hex_to_dec(regist[0])], 4);
		write_from_tab2((e->process[xproc].position + (i[3] % (IDX_MOD))), 4, e->process[xproc].id_player + 1);
	}
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
