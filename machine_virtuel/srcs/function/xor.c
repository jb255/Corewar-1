/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:40:11 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/15 16:38:33 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

void	xor_func(t_env *e, int xproc, t_type_func list)
{
	int		i[4];
	int		place;
	int		error;

	place = 3;
	error = 0;
	i[0] = get_i02_func_and(list, e, xproc, &place); // VALUE du reg
	i[1] = get_i1_2_func_and(list, e, xproc, &place);
	i[2] = to_int_getx(get_x_from_position(e, e->process[xproc].position + place, e->process[xproc].position + (place + 1))); // Arg3
	i[3] = (i[0] ^ i[1]);
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
