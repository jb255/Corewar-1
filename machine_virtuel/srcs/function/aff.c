/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:20:03 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 15:29:48 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

void	aff_func(t_env *e, int xproc, t_type_func list)
{
	(void)e;
	(void)xproc;
	(void)list;

	e->process[xproc].position = (e->process[xproc].position + 1) % MEM_SIZE;

}
