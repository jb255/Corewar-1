/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:30:41 by viko              #+#    #+#             */
/*   Updated: 2016/12/20 02:31:20 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		get_lldi_arg(t_type_a list, t_env *e, int xproc, int *place)
{
	int		i;
	int		pos;

	i = 0;
	pos = e->process[xproc].position;
	if (*place == -1)
		return (i);
	if (list.t_reg && (*place += 1))
	{
		i = reg_funcheck_and(e, xproc, *place);
		if (i > 16 || i < 1)
			*place = -1;
		else
			i = e->process[xproc].reg[i];
	}
	else if (list.t_ind && (*place += 2))
	{
		i = (short)to_int_getx(get_x(e, pos + *place - 2, pos + *place));
		i = to_int_getx(get_x(e, pos + i, pos + i + 4));
	}
	else if (list.t_dir && (*place += 2))
		i = (short)to_int_getx(get_x(e, pos + *place - 2, pos + *place));
	return (i);
}

/*
** ft_printf_fd(e->fd, "Value ldi to search %d\n", i[2]);
*/

void	lldi_func(t_env *e, int xproc, t_type_func list)
{
	int		i[5];
	int		place;
	int		error;

	error = 0;
	place = 2;
	if (list.type[2].t_ind || list.type[2].t_dir || list.type[1].t_ind)
	{
		error = 1;
		place = -1;
	}
	// else
		// ft_printf_fd(e->fd, "P\t%d | lldi", xproc);
	i[0] = get_lldi_arg(list.type[0], e, xproc, &place);
	i[1] = get_lldi_arg(list.type[1], e, xproc, &place);
	i[3] = to_int_getx(get_x(e, e->process[xproc].position + place, e->process[xproc].position + (place + 1)));
	(i[3] > 16 || i[3] < 1) ? (error = 1) : error;
	i[2] = ((i[0] + i[1])) % MEM_SIZE;
	i[4] = to_int_getx(get_x(e, e->process[xproc].position + i[2], e->process[xproc].position + i[2] + REG_SIZE));
	(place == -1) ? (error = 1) : error;
	// if (!error)
		// ft_printf_fd(e->fd, " %d\n\t-> load from %d + %d = %d (with pc %d // pc = %d[%s])", i[3], i[1], i[0], i[2], e->process[xproc].position + i[2], e->process[xproc].position, get_x(e, e->process[xproc].position + i[2], e->process[xproc].position + i[2] + REG_SIZE));
	if (!error)
		e->process[xproc].reg[i[3]] = i[4];
	if (i[4] && !error)
		e->process[xproc].carry = 0;
	else if (!error)
		e->process[xproc].carry = 1;
	e->process[xproc].position = (e->process[xproc].position +
		list.size) % MEM_SIZE;
	ft_printf_fd(e->fd, "\n");
}
