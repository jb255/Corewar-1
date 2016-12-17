/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:19:51 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/17 03:31:24 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

// p1 & p2 -> p3. Le paramètre 3 est toujours un registre.
// Cette opération modifie le carry.
// and r2, %0,r3 met r2 & 0 dans r3
// {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}

int		reg_funcheck_and(t_env *e, int xproc, int place)
{
	char	*result;
	int		i;

	i = 0;
	result = get_x_from_position(e, e->process[xproc].position + ((place - 1) % IDX_MOD), e->process[xproc].position + (place % IDX_MOD));
	i = hex_to_dec(result);
	free(result);
	return (i);
}

void	and_func(t_env *e, int xproc, t_type_func list)
{
	int		i[4];
	int		place;
	int		error;

	error = 0;
	place = 2;
	i[0] = get_xorandor_arg(list.type[0], e, xproc, &place); // VALUE du reg
	i[1] = get_xorandor_arg(list.type[1], e, xproc, &place);
	i[2] = to_int_getx(get_x_from_position(e, e->process[xproc].position + place, e->process[xproc].position + (place + 1))); // Arg3
	ft_printf_fd(e->fd, "Arg1[%d] // Arg2[%d] // Arg3[%d]\n", i[0], i[1], i[2]);
	i[3] = (i[0] & i[1]);
	ft_printf_fd(e->fd, "result i[3] = %d\n", i[3]);
	if (place == -1)
		error = 1;
	if (!error)
		e->process[xproc].reg[i[2]] = i[3];
	if (i[3] && !error)
		e->process[xproc].carry = 0;
	else if (!error)
		e->process[xproc].carry = 1;
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
