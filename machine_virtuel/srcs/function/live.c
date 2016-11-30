/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/30 12:25:26 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

int		check_live(t_env *e, int xproc, t_type_func list)
{
	(void)e;
	(void)xproc;
	(void)list;
	ft_putstr_fd("Check_live -- Fonction\n", e->fd);
	return (1);
}

void	live_func(t_env *e, int xproc, t_type_func list)
{
	char		*result;

	(void)list;
	result = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 5);
	name_process(e, result);
	free(result);
	// nodelay(stdscr, 1);
	// getch();
}
