/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 17:29:51 by viko              #+#    #+#             */
/*   Updated: 2016/12/03 17:30:16 by viko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		check_lfork(t_env *e, int xproc, t_type_func list)
{
	ft_printf_fd(e->fd, "Check_lfork -- Fonction size %d\n", list.size);
	(void)xproc;
	(void)list;

	return (1);
}

void	lfork_func(t_env *e, int xproc, t_type_func list)
{
	char		*new_start;
	int			position;

	new_start = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 3);
	position = e->process[xproc].position + (hex_to_dec(new_start));
	ft_printf_fd(e->fd, "-----lFork New Process at %d\n", position);
	set_process(e, e->active_process++, position, e->process[xproc].id_player);
	free(new_start);
	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
}
