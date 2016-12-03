/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:30:41 by viko              #+#    #+#             */
/*   Updated: 2016/12/03 17:37:10 by viko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		check_lldi(t_env *e, int xproc, t_type_func list)
{
	ft_printf_fd(e->fd, "Check_lldi -- Fonction size %d\n", list.size);
	(void)xproc;
	(void)list;

	return (1);
}

void	lldi_func(t_env *e, int xproc, t_type_func list)
{
	char	*regist[2];
	int		i[3];
	int		place;
	int		error;

	error = 0;
	place = 0;
	i[0] = get_i02_func_and(list, e, xproc, &place);
	if (list.type[0].t_reg && (i[0] > 16 || i[0] < 1))
		error = 1;
	else if (list.type[0].t_reg)
		i[0] = e->process[xproc].reg[i[0]];
	i[1] = get_i1_2_func_and(list, e, xproc, &place);
	if (list.type[1].t_reg && (i[1] > 16 || i[1] < 1))
		error = 1;
	else if (list.type[1].t_reg)
		i[1] = e->process[xproc].reg[i[1]];
	i[2] = i[1] + i[0]; // Ajout de l'arg 2 a l'arg 1
	regist[0] = get_x_from_position(e, e->process[xproc].position + (place), e->process[xproc].position + (place + 1));
	regist[1] = get_x_from_position(e, e->process[xproc].position + (i[2]), e->process[xproc].position + ((i[2] + REG_SIZE)));
	ft_printf_fd(e->fd, "Check_lldi -- Registre[%s] Value[%d] + Value1[%d] = Value2[%d], Result a l'addr value2 [%s]\n", regist[0], i[0], i[1], i[2], regist[1]);
	if (hex_to_dec(regist[0]) > 16 || hex_to_dec(regist[0]) < 1)
		error = 1;
	if (!error)
		e->process[xproc].reg[hex_to_dec(regist[0])] = hex_to_dec(regist[1]);
	ft_printf_fd(e->fd, "Check_lldi -- RESULT du Registre[%s] qui a ete recherché a l'adresse {%d} = %s and %08x\n", regist[0], i[0], regist[1], hex_to_dec(regist[1]));
	free(regist[0]);
	free(regist[1]);
	ft_printf_fd(e->fd, "Check_lldi -- Value final du Registre1 [%d]\n", e->process[xproc].reg[1]);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
