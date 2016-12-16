/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:40:11 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/15 22:00:19 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		get_xorandor_arg(t_type_a list, t_env *e, int xproc, int *place)
{
	int		i;

	i = 0;
	if (*place == -1)
		return (i);
	if (list.t_reg && (*place += 1))
	{
		i = reg_funcheck_and(e, xproc, *place);
		if (i > 16 || i < 1)
			*place = -1;
		i = e->process[xproc].reg[i];
	}
	else if (list.t_ind && (*place += 2))
	{
		i = (short)to_int_getx(get_x_from_position(e, e->process[xproc].position + *place - 2, e->process[xproc].position + *place)) % IDX_MOD;
		i = to_int_getx(get_x_from_position(e, e->process[xproc].position  + i, e->process[xproc].position + i  + 4)) ;
	}
	else if (list.t_dir && (*place += 4)){
		i = to_int_getx(get_x_from_position(e, e->process[xproc].position + *place - 4, e->process[xproc].position + *place));
		ft_printf_fd(e->fd, "Valeur du direct %d\n", i);
	}
	return (i);
}

void	xor_func(t_env *e, int xproc, t_type_func list)
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
	i[3] = (i[0] ^ i[1]);
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

// void	xor_func(t_env *e, int xproc, t_type_func list)
// {
// 	char	*regist;
// 	int		i[2];
// 	int		place;
// 	int		error;
//
// 	place = 0;
// 	error = 0;
// 	i[0] = get_i0_func_and(list, e, xproc, &place);
// 	if (list.type[0].t_reg && (i[0] > 16 || i[0] < 1))
// 		error = 1;
// 	else if (list.type[0].t_reg) // A tester
// 		i[0] = e->process[xproc].reg[i[0]]; // A tester
// 	i[1] = get_i1_func_and(list, e, xproc, &place);
// 	if (list.type[1].t_reg && (i[1] > 16 || i[1] < 1))
// 		error = 1;
// 	else if (list.type[1].t_reg)// A tester
// 		i[1] = e->process[xproc].reg[i[1]]; // A tester
// 	regist = get_x_from_position(e, e->process[xproc].position + (place % IDX_MOD), e->process[xproc].position + (place + 1 % IDX_MOD));
// 	if (hex_to_dec(regist) > 16 || hex_to_dec(regist) < 1)
// 		error = 1;
// 	if (!error)
// 		e->process[xproc].reg[hex_to_dec(regist)] = i[0] ^ i[1];
// 	free(regist);
// 	if (e->process[xproc].reg[hex_to_dec(regist)])
// 		e->process[xproc].carry = 0;
// 	else if (!error)
// 		e->process[xproc].carry = 1;
// 	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
// }
