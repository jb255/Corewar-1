/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 04:07:26 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/06 17:05:45 by vlancien         ###   ########.fr       */
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
	(void)e;
	// ft_putstr_fd("Check_st -- Fonction\n", e->fd);
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
	int				regist = 0;

	ft_printf_fd(e->fd, "Fonction st lancement size %d, t_reg[%d], t_reg1[%d], t_ind1[%d]\n", list.size, list.type[0].t_reg, list.type[1].t_reg, list.type[1].t_ind);
	if (list.type[0].t_reg)
		reg = tab[e->process[xproc].position + 2];
	if (list.type[0].t_reg && list.type[1].t_reg)
	{
		regist = e->process[xproc].reg[tab[e->process[xproc].position + 3]];
		e->process[xproc].reg[reg] = regist;
		ft_printf_fd(e->fd, "ERROR");
	}
	else if (list.type[0].t_reg && list.type[1].t_ind)
	{
		ft_printf_fd(e->fd, "--------------%d-xproc=%d---------------\n", e->process[xproc].id_player, xproc);
		result = get_x_from_position(e, e->process[xproc].position + 3, e->process[xproc].position + 5);
		regist = (signed short)hex_to_dec(result);
		ft_printf_fd(e->fd, "------Search begin at: %d at: %d, value of reg %d\n", regist, (e->process[xproc].position + (regist % IDX_MOD)), e->process[xproc].reg[reg]);
		write_from_x(e, (e->process[xproc].position + (regist % (IDX_MOD))), e->process[xproc].reg[reg], 4);
		int y = (e->process[xproc].position + (regist % (IDX_MOD)));
		y = y < 0 ? MEM_SIZE + y : y;
		ft_printf_fd(e->fd, "Position[%d], Size[%d], index[%d]\n", y, 4, y + 4);
		write_from_tab2(y, 4, e->process[xproc].id_player + 1);
		free(result);
		ft_printf_fd(e->fd, "Next ft_func\n");
	}
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
