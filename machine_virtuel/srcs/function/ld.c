/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:00:22 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/16 06:40:36 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	ld_func(t_env *e, int xproc, int func)
{
	t_type_func	list;
	int			position;
	char		*hex = NULL;
	char		*reg = NULL;

	(void)func;
	position = e->process[xproc]->position;
	list = check_jump(e, hex_to_bin_quad(get_op_str(tab[(position + 2) %
	((MEM_SIZE) * 2)], tab[(position + 3) % ((MEM_SIZE) * 2)])));
	if (list.type[0].t_dir)
		hex = get_opfrom_x(e, position + 4, position + 12);
	else if (list.type[0].t_ind)
		hex = get_opfrom_x(e, position + 4, position + 8);
	if (list.type[1].t_reg && list.type[0].t_ind)
		reg = get_opfrom_x(e, position + 8, position + 10);
	else if (list.type[1].t_reg && list.type[0].t_dir)
		reg = get_opfrom_x(e, position + 12, position + 14);
	if (!list.type[1].t_reg || (!list.type[0].t_ind && !list.type[0].t_dir) || list.type[0].t_reg)
		e->process[xproc]->jumptodo = 2;
	else
	{
		e->process[xproc]->reg[ft_atoi(reg)] = hex_to_dec(hex);
		e->process[xproc]->carry = 1;
	}
	free(reg);
	free(hex);
	nodelay(stdscr, 0);
	getch();
	nodelay(stdscr, 1);
}
