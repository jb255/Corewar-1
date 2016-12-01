/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:39:34 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/01 18:07:09 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>
// Cette opération modifie le carry.
// ldi 3,%4,r1 lit IND_SIZE octets a l’adresse : (PC + (3 % IDX_MOD)) ajoute 4 à cette valeur.
// On nommera S cette somme. On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD)) que l’on copie dans r1.
// Les paramètres 1 et 2 sont des index.
// T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG
int		check_ldi(t_env *e, int xproc, t_type_func list)
{
	ft_printf_fd(e->fd, "Check_ldi -- Fonction size %d\n", list.size);
	(void)xproc;
	(void)list;

	return (1);
}

int		get_i02_func_and(t_type_func list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	if (list.type[0].t_reg && (*place = 3))
		i = reg_funcheck_and(e, xproc, *place);
	else if (list.type[0].t_ind && (*place = 4))
		i = ind_funcheck_and(e, xproc, *place, list.type[0]);
	else if (list.type[0].t_dir && (*place = 4))
		i = ind_funcheck_and(e, xproc, *place, list.type[0]);
	return (i);
}

int		get_i1_2_func_and(t_type_func list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	if (list.type[1].t_reg && (*place += 1))
		i = reg_funcheck_and(e, xproc, *place);
	else if (list.type[0].t_ind && (*place += 2))
		i = ind_funcheck_and(e, xproc, *place, list.type[1]);
	else if (list.type[1].t_dir && (*place += 2))
		i = ind_funcheck_and(e, xproc, *place, list.type[1]);
	return (i);
}

void	ldi_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist[2];
	int		i[2];
	int		place;
	int		error;

	error = 0;
	place = 0;
	i[0] = get_i02_func_and(list, e, xproc, &place);
	if (list.type[0].t_reg && (i[0] > 16 || i[0] < 1))
		error = 1;
	i[1] = get_i1_2_func_and(list, e, xproc, &place);
	if (list.type[1].t_reg && (i[1] > 16 || i[1] < 1))
		error = 1;
	i[0] += i[1]; // Ajout de l'arg 2 a l'arg 1
	regist[0] = get_x_from_position(e, e->process[xproc].position + (place % IDX_MOD), e->process[xproc].position + (place + 1 % IDX_MOD));
	regist[1] = get_x_from_position(e, e->process[xproc].position + (i[0] % IDX_MOD), e->process[xproc].position + ((i[0] + REG_SIZE) % IDX_MOD));
	ft_printf_fd(e->fd, "Check_ldi -- %d & %d , r%d\n", i[0], i[1], hex_to_dec(regist[0]));
	if (hex_to_dec(regist[0]) > 16 || hex_to_dec(regist[0]) < 1)
		error = 1;
	if (!error)
		e->process[xproc].reg[hex_to_dec(regist[0])] = hex_to_dec(regist[1]);
	free(regist[0]);
	free(regist[1]);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
