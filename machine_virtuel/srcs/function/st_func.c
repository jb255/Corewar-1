/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 04:07:26 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 00:06:53 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// • st : Prend un registre et un registre ou un indirect,
// et stocke la valeur du registre vers le second paramètre.
// Son opcode est 0x03. Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
// (PC + (42 % IDX_MOD))
// {T_REG, T_IND | T_REG}

void	st_func(t_env *e, int xproc, t_type_func list)
{
	int				reg = 0;
	int				regist = 0;
	int				error;
	int 			y;

	error = 0;
	ft_printf_fd(e->fd, "P\t%d | st", xproc);
	if (list.type[0].t_reg){
		reg = to_int_getx(get_x(e, e->process[xproc].position + 2, e->process[xproc].position + 3));
		ft_printf_fd(e->fd, " r%d", reg);
	}
	else
		error = 1;
	(reg > 16 || reg < 1) ? (error = 1) : error;
	if (list.type[1].t_reg && !error)
	{
		regist = to_int_getx(get_x(e, e->process[xproc].position + 3, e->process[xproc].position + 4));
		(regist > 16 || regist < 1) ? (error = 1) : error;
		ft_printf_fd(e->fd, " r%d", regist);
		if (!error)
		{
			regist = e->process[xproc].reg[regist];
			e->process[xproc].reg[reg] = regist;
		}
	}
	else if (list.type[1].t_ind && !error)
	{
		regist = (short)to_int_getx(get_x(e, e->process[xproc].position + 3, e->process[xproc].position + 5));
		ft_printf_fd(e->fd, " %d", regist);
		y = (e->process[xproc].position + (regist % IDX_MOD)) % MEM_SIZE;
		write_from_x(e, y, e->process[xproc].reg[reg], 4);
		write_from_tab2(y, 4, e->process[xproc].id_player + 1);
	}
	ft_printf_fd(e->fd, "\n");
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
