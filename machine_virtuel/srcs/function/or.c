/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:38:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/01 15:23:28 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		check_or(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	(void)xproc;
	ft_printf_fd(e->fd, "Check_or -- Fonction\n");
	if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && !list.type[1].t_reg)
		return (1);
	if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && list.type[1].t_reg && is_register_valid(e, xproc, 3) && list.type[2].t_reg && is_register_valid(e, xproc, 4))
		return (1);
	return (0);
}

void	or_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist;
	int		i[2];
	int		place;
	int		error;

	place = 0;
	error = 0;
	ft_printf_fd(e->fd, "Check_or -- ENTER\n");
	i[0] = get_i0_func_and(list, e, xproc, &place);
	if (list.type[0].t_reg && (i[0] > 16 || i[0] < 1))
		error = 1;
	i[1] = get_i1_func_and(list, e, xproc, &place);
	if (list.type[1].t_reg && (i[1] > 16 || i[1] < 1))
		error = 1;
	regist = get_x_from_position(e, e->process[xproc].position + (place % IDX_MOD), e->process[xproc].position + (place + 1 % IDX_MOD));
	if (hex_to_dec(regist) > 16 || hex_to_dec(regist) < 1)
		error = 1;
	ft_printf_fd(e->fd, "Check_or -- %d & %d = %d\n", i[0], i[1], i[0] | i[1]);
	if (!error)
		e->process[xproc].reg[hex_to_dec(regist)] = i[0] | i[1];
	ft_printf_fd(e->fd, "--->Function or\n--->Registre %d update:  [%d]\n", hex_to_dec(regist), e->process[xproc].reg[hex_to_dec(regist)]);
	free(regist);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
