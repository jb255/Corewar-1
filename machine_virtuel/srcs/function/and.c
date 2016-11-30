/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:19:51 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/30 13:38:34 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

// p1 & p2 -> p3. Le paramètre 3 est toujours un registre.
// Cette opération modifie le carry.
// and r2, %0,r3 met r2 & 0 dans r3
// {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}

int		check_and(t_env *e, int xproc, t_type_func list)
{
	(void)list;
	(void)xproc;
	ft_printf_fd(e->fd, "Check_and -- Fonction\n");
	// if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && !list.type[1].t_reg)
	// 	return (1);
	// if (list.type[0].t_reg && is_register_valid(e, xproc, 2) && list.type[1].t_reg && is_register_valid(e, xproc, 3) && list.type[2].t_reg && is_register_valid(e, xproc, 4))
	// 	return (1);
	return (1);
}

int		reg_funcheck_and(t_env *e, int xproc, int place)
{
	char	*result;
	int		i;

	i = 0;
	result = get_x_from_position(e, e->process[xproc].position + (place - 1 % IDX_MOD), e->process[xproc].position + (place % IDX_MOD));
	i = e->process[xproc].reg[hex_to_dec(result)];
	free(result);
	return (i);
}
int		ind_funcheck_and(t_env *e, int xproc, int place, t_type_a type)
{
	char	*result[2];
	int		i;

	i = 0;
	if (type.t_dir){
		result[0] = get_x_from_position(e, e->process[xproc].position + (place - 2 % IDX_MOD), e->process[xproc].position + (place % IDX_MOD));
		i = hex_to_dec(result[0]);
		ft_printf_fd(e->fd, "Check_and/or -- value du DIR [%s]", result[0]);

	}
	else if (type.t_ind)
	{
		result[0] = get_x_from_position(e, e->process[xproc].position + place - 2, e->process[xproc].position + place);
		result[1] = get_x_from_position(e, e->process[xproc].position + (hex_to_dec(result[0]) % IDX_MOD), e->process[xproc].position + (hex_to_dec(result[0]) + IND_SIZE % IDX_MOD));
		i = hex_to_dec(result[1]);
		ft_printf_fd(e->fd, "Check_and/or -- addr [%s] value du IND [%s]", result[0], result[1]);

		free(result[1]);
	}
	free(result[0]);
	return (i);
}

void	and_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist;
	int		i[2];
	int		place;

	place = 0;
	ft_printf_fd(e->fd, "Check_and -- ENTER\n");
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
	ft_printf_fd(e->fd, "Check_and -- %d & %d = %d\n", i[0], i[1], i[0] & i[1]);
	e->process[xproc].reg[hex_to_dec(regist)] = i[0] & i[1];
	ft_printf_fd(e->fd, "--->Function and\n--->Registre %d update:  [%d]\n", hex_to_dec(regist), e->process[xproc].reg[hex_to_dec(regist)]);
	free(regist);
}
