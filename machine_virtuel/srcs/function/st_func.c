/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 04:07:26 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/03 17:44:42 by viko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// • st : Prend un registre et un registre ou un indirect,
// et stocke la valeur du registre vers le second paramètre.
// Son opcode est 0x03. Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
// (PC + (42 % IDX_MOD))
// {T_REG, T_IND | T_REG}

int		check_st(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	(void)xproc;
	ft_putstr_fd("Check_st -- Fonction\n", e->fd);
	// if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && list.type[1].t_ind)
	// 	return (1);
	// if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && list.type[1].t_reg && is_register_valid(e, xproc, 3))
	// 	return (1);
	return (1);
}

void	st_func(t_env *e, int xproc, t_type_func list)
{
	char			*result = "";
	int				reg = 0;
	int			regist = 0;

	if (list.type[0].t_reg)
		reg = tab[e->process[xproc].position + 2];
	if (list.type[0].t_reg && list.type[1].t_reg)
	{
		regist = e->process[xproc].reg[tab[e->process[xproc].position + 3]];
		e->process[xproc].reg[reg] = regist;
	}
	else if (list.type[0].t_reg && list.type[1].t_ind)
	{
		result = get_x_from_position(e, e->process[xproc].position + 3, e->process[xproc].position + 5);
		ft_printf_fd(e->fd, "------------->Function-ST Search from %d to %d, result [%s]\nRegistre %d du joueur %d contient %d\nPC ADDR [%d]\n", e->process[xproc].position + 3, e->process[xproc].position + 5, result, reg, xproc, e->process[xproc].reg[reg], e->process[xproc].addr_pc);
		regist = hex_to_dec(result);
		write_from_x(e, (e->process[xproc].position + (regist % (IDX_MOD))), e->process[xproc].reg[reg], 4);
		write_from_tab2((e->process[xproc].position + (regist % (IDX_MOD))), 4, e->process[xproc].id_player + 1);
	}
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
	// if (!list.type[0].t_reg || (!list.type[1].t_reg && !list.type[1].t_ind))
	// 	e->process[xproc].jumptodo = 1;
	free(result);
}
