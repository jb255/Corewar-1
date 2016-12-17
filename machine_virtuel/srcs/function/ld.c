/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:00:22 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/17 03:24:40 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// Cette instruction prend 2 paramètres, le deuxième est forcément un registre
// (pas le PC). Elle load la valeur du premier paramètre dans le registre.
// Cette opération modifie le carry.
// ld 34,r3 charge les REG_SIZE octets à partir de l’adresse (PC + (34 % IDX_MOD)) dans le registre r3.
// {T_DIR | T_IND, T_REG},

int		to_int_getx(char *str)
{
	int		nb;

	nb = hex_to_dec(str);
	free(str);
	return (nb);
}

int		get_first_ld(t_env *e, t_type_func list, int *error, int xproc)
{
	int		result;

	result = 0;
	if (list.type[0].t_dir)
		result = to_int_getx(get_x_from_position(e, e->process[xproc].position + 2, e->process[xproc].position + 6));
	else if (list.type[0].t_ind)
		result = to_int_getx(get_x_from_position(e, e->process[xproc].position + 2, e->process[xproc].position + 4));
	else
		*error = 1;
	return (result);
}

void	ld_func(t_env *e, int xproc, t_type_func list)
{
	int			position;
	int			reg;
	int			place;
	int			error;
	int			value;

	place = 0;
	reg = 0;
	error = 0;
	// ft_printf_fd(e->fd, "ld ");
	value = get_first_ld(e, list, &error, xproc);
	list.type[0].t_ind == 1 ? (place = 4) : place;
	list.type[0].t_dir == 1 ? (place = 6) : place;
	if (list.type[1].t_reg && !error)
		reg = to_int_getx(get_x_from_position(e, e->process[xproc].position + place, e->process[xproc].position + (place + 1)));
	(reg > 16 || reg < 1) ? (error = 1) : error;
	if (list.type[0].t_ind && list.type[1].t_reg && !error)
	{
		position = e->process[xproc].position + (value % IDX_MOD);
		value = to_int_getx(get_x_from_position(e, position, position + REG_SIZE));
	}
	ft_printf_fd(e->fd, "P\t%d | ld %d r%d\n", xproc, value, reg);

	if (!error)
		e->process[xproc].reg[reg] = value;
	if (value && !error)
		e->process[xproc].carry = 0;
	else if (!error)
		e->process[xproc].carry = 1;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
