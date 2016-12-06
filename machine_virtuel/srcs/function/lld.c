/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:31:30 by viko              #+#    #+#             */
/*   Updated: 2016/12/06 16:01:41 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

int		check_lld(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	(void)xproc;
	ft_printf_fd(e->fd, "Check_lld -- Fonction size %d\n", list.size);
	if (is_register_valid(e, xproc, 4))
		return (1);
	return (0);
}

void	lld_func(t_env *e, int xproc, t_type_func list)
{
	char		*value = NULL;
	char		*reg = NULL;
	int			position;

	position = 0;
	e->process[xproc].carry = 1;
	if (list.type[0].t_dir)
		value = get_x_from_position(e, e->process[xproc].position + 2, e->process[xproc].position + 6);
	else if (list.type[0].t_ind)
		value = get_x_from_position(e, e->process[xproc].position + 2, e->process[xproc].position + 4);
	if (list.type[1].t_reg && !list.type[0].t_dir)
		reg = get_x_from_position(e, e->process[xproc].position + 4, e->process[xproc].position + 5);
	else if (list.type[1].t_reg && list.type[0].t_dir)
		reg = get_x_from_position(e, e->process[xproc].position + 6, e->process[xproc].position + 7);
	if (list.type[0].t_ind && list.type[1].t_reg)
	{
		position = e->process[xproc].position + (hex_to_dec(value)); // Addr pc maybe wrong
		value = get_x_from_position(e, position, position + REG_SIZE - 1);
		e->process[xproc].reg[hex_to_dec(reg)] = hex_to_dec(value);
	}
	else if (list.type[0].t_dir && list.type[1].t_reg)
		e->process[xproc].reg[hex_to_dec(reg)] = hex_to_dec(value);
	if ((list.type[0].t_dir || list.type[0].t_ind) && list.type[0].t_reg && hex_to_dec(value) == 0)
		e->process[xproc].carry = 1;
	ft_printf_fd(e->fd, "---------->REGISTRE %d | value = [%d]\n", hex_to_dec(reg), hex_to_dec(value));
	free(reg);
	free(value);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;

	// nodelay(stdscr, 0);
	// getch();
	// nodelay(stdscr, 1);
}
