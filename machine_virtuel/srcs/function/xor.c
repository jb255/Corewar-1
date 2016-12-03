/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:40:11 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/03 01:45:03 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		check_xor(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	(void)xproc;
	ft_printf_fd(e->fd, "Check_xor -- Fonction, size %d\n", list.size);

	// if (list.type[0].t_reg && is_register_valid(e, xproc, 2))
	// 	return (1);
	// if (list.type[2].t_reg && is_register_valid(e, xproc, list.size - 1))
	// 	return (1);
	// if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && list.type[1].t_reg && is_register_valid(e, xproc, 3) && list.type[2].t_reg && is_register_valid(e, xproc, 4))
	// 	return (1);
	return (1);
}

void	xor_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist;
	int		i[2];
	int		place;
	int		error;

	place = 0;
	error = 0;
	ft_printf_fd(e->fd, "Check_xor -- ENTER\n");
	i[0] = get_i0_func_and(list, e, xproc, &place);
	if (list.type[0].t_reg && (i[0] > 16 || i[0] < 1))
		error = 1;
	else if (list.type[0].t_reg) // A tester
		i[0] = e->process[xproc].reg[i[0]]; // A tester
	i[1] = get_i1_func_and(list, e, xproc, &place);
	if (list.type[1].t_reg && (i[1] > 16 || i[1] < 1))
		error = 1;
	else if (list.type[1].t_reg)// A tester
		i[1] = e->process[xproc].reg[i[1]]; // A tester
	regist = get_x_from_position(e, e->process[xproc].position + (place % IDX_MOD), e->process[xproc].position + (place + 1 % IDX_MOD));
	if (hex_to_dec(regist) > 16 || hex_to_dec(regist) < 1)
		error = 1;
	ft_printf_fd(e->fd, "Check_xor -- %d & %d = %d\n", i[0], i[1], i[0] | i[1]);
	if (!error)
		e->process[xproc].reg[hex_to_dec(regist)] = i[0] ^ i[1];
	ft_printf_fd(e->fd, "--->Function xor\n--->Registre %d update:  [%d]\n", hex_to_dec(regist), e->process[xproc].reg[hex_to_dec(regist)]);
	free(regist);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
