/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:00:22 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/06 16:01:25 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// Cette instruction prend 2 paramètres, le deuxième est forcément un registre
// (pas le PC). Elle load la valeur du premier paramètre dans le registre.
// Cette opération modifie le carry.
// ld 34,r3 charge les REG_SIZE octets à partir de l’adresse (PC + (34 % IDX_MOD)) dans le registre r3.
// {T_DIR | T_IND, T_REG},
int		check_ld(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	(void)xproc;
	ft_printf_fd(e->fd, "Check_ld -- Fonction size %d\n", list.size);
	// if (is_register_valid(e, xproc, 4))
	// 	return (1);
	return (1);
}

void	ld_func(t_env *e, int xproc, t_type_func list)
{
	char		*value = NULL;
	char		*reg = NULL;
	int			position;

	position = 0;
	// ft_printf_fd(e->fd, "----LD FUNC dir[%d] ind[%d] reg1[%d]\n", list.type[0].t_dir, list.type[0].t_ind, list.type[1].t_reg);
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
		position = e->process[xproc].position + (hex_to_dec(value) % IDX_MOD); // Addr pc maybe wrong
		value = get_x_from_position(e, position, position + REG_SIZE - 1);
		e->process[xproc].reg[hex_to_dec(reg)] = hex_to_dec(value);
	}
	else if (list.type[0].t_dir && list.type[1].t_reg)
		e->process[xproc].reg[hex_to_dec(reg)] = hex_to_dec(value);
	if ((list.type[0].t_dir || list.type[0].t_ind) && list.type[0].t_reg && hex_to_dec(value) == 0)
		e->process[xproc].carry = 1;
	// ft_printf_fd(e->fd, "---------->REGISTRE %d | value = [%d]\n", hex_to_dec(reg), hex_to_dec(value));
	if (reg)
		free(reg);
	if (value)
		free(value);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;

	// nodelay(stdscr, 0);
	// getch();
	// nodelay(stdscr, 1);
}
