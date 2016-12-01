/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:21 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/01 12:01:04 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// Cette instruction prend 3 registres en paramètre,
// additionne le contenu des 2 premiers et met le résultat dans le troisième.
// Cette opération modifie le carry.
// add r2,r3,r5 additionne r2 et r3 et met le résultat dans r5

int		check_add(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	(void)xproc;
	ft_putstr_fd("Check_add|sub -- Fonction\n", e->fd);
	if (is_register_valid(e, xproc, 2) && is_register_valid(e, xproc, 3) && is_register_valid(e, xproc, 4)){
		ft_putstr_fd("Check_add|sub -- Les registres sont corrects\n", e->fd);
		return (1);
	}
	// ft_putstr_fd("Check_add|sub -- Error\n", e->fd);
	return (0);
}

void	add_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist[3];

	regist[0] = get_x_from_position(e, 2, 3);
	regist[1] = get_x_from_position(e, 3, 4);
	regist[2] = get_x_from_position(e, 4, 5);
	if (list.type[0].t_reg && list.type[1].t_reg && list.type[2].t_reg)
		e->process[xproc].reg[hex_to_dec(regist[2])] =
		e->process[xproc].reg[hex_to_dec(regist[0])] +
		e->process[xproc].reg[hex_to_dec(regist[1])];
	ft_printf_fd(e->fd, "--->Function add\n--->Registre %d update:  [%d]\n", hex_to_dec(regist[2]), e->process[xproc].reg[hex_to_dec(regist[2])]);
	free(regist[0]);
	free(regist[1]);
	free(regist[2]);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
