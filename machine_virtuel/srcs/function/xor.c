/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:40:11 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/30 15:55:00 by vlancien         ###   ########.fr       */
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

	place = 0;
	ft_printf_fd(e->fd, "Check_xor -- ENTER\n");
	if (list.type[0].t_reg && (place = 3))
		i[0] = reg_funcheck_and(e, xproc, place);
	else if (list.type[0].t_ind && (place = 4))
		i[0] = ind_funcheck_and(e, xproc, place, list.type[0]);
	else if (list.type[0].t_dir && (place = 6))
		i[0] = ind_funcheck_and(e, xproc, place, list.type[0]);
	if (list.type[1].t_reg && (place += 1))
		i[1] = reg_funcheck_and(e, xproc, place);
	else if (list.type[0].t_ind && (place += 2))
		i[1] = ind_funcheck_and(e, xproc, place, list.type[1]);
	else if (list.type[1].t_dir && (place += 4))
		i[1] = ind_funcheck_and(e, xproc, place, list.type[1]);
	regist = get_x_from_position(e, e->process[xproc].position + (place % IDX_MOD), e->process[xproc].position + (place + 1 % IDX_MOD));
	ft_printf_fd(e->fd, "Check_xor -- %d & %d = %d\n", i[0], i[1], i[0] | i[1]);
	e->process[xproc].reg[hex_to_dec(regist)] = i[0] ^ i[1];
	ft_printf_fd(e->fd, "--->Function xor\n--->Registre %d update:  [%d]\n", hex_to_dec(regist), e->process[xproc].reg[hex_to_dec(regist)]);
	free(regist);
}
