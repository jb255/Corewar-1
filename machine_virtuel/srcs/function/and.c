/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:19:51 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/29 18:46:00 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

// p1 & p2 -> p3. Le paramètre 3 est toujours un registre.
// Cette opération modifie le carry.
// and r2, %0,r3 met r2 & 0 dans r3
// {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}

int		check_and(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	ft_putstr_fd("Check_st -- Fonction\n", e->fd);
	if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && !list.type[1].t_reg)
		return (1);
	if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && list.type[1].t_reg && is_register_valid(e, xproc, 3))
		return (1);
	return (0);
}

void	and_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist[3];

	regist[0] = get_x_from_position(e, xproc, 2, 3);
	regist[1] = get_x_from_position(e, xproc, 3, 4);
	regist[2] = get_x_from_position(e, xproc, 4, 5);
	if (list.type[0].t_reg && list.type[1].t_reg && list.type[2].t_reg)
		e->process[xproc].reg[hex_to_dec(regist[2])] =
		e->process[xproc].reg[hex_to_dec(regist[0])] &
		e->process[xproc].reg[hex_to_dec(regist[1])];
	ft_printf_fd(e->fd, "--->Function and\n--->Registre %d update:  [%d]\n", hex_to_dec(regist[2]), e->process[xproc].reg[hex_to_dec(regist[2])]);
	free(regist[0]);
	free(regist[1]);
	free(regist[2]);
}
