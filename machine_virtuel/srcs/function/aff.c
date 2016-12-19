/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:20:03 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 00:58:01 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	aff_func(t_env *e, int xproc, t_type_func list)
{
	int		reg;

	reg = to_int_getx(get_x(e, e->process[xproc].position + 2,
		e->process[xproc].position + 3));
	if (!e->flag.flag_n && list.type[0].t_reg)
		ft_printf("%c", e->process[xproc].reg[reg] % 256);
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
}
