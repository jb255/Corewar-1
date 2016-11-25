/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:34 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/25 06:39:22 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// void	sub_func(t_env *e, int xproc, int func)
// {
// 	char	r[3][2];
//
// 	r[0][0] = (e->process[xproc]->position + 4) % ((MEM_SIZE));
// 	r[0][1] = (e->process[xproc]->position + 5) % ((MEM_SIZE));
// 	r[1][0] = (e->process[xproc]->position + 6) % ((MEM_SIZE));
// 	r[1][1] = (e->process[xproc]->position + 7) % ((MEM_SIZE));
// 	r[2][0] = (e->process[xproc]->position + 7) % ((MEM_SIZE));
// 	r[2][1] = (e->process[xproc]->position + 8) % ((MEM_SIZE));
// 	if (func == 4)
// 		e->process[xproc]->reg[ft_atoi(r[2])] = e->process[xproc]->reg[ft_atoi(r[0])] - e->process[xproc]->reg[ft_atoi(r[1])];
// }
