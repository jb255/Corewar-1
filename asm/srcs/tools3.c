/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:41:35 by jaustry           #+#    #+#             */
/*   Updated: 2016/12/07 15:41:37 by jaustry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

unsigned int	little_to_big(unsigned int little)
{
	unsigned int	big;

	big = ((little >> 24) & 0xff) | ((little << 8) & 0xff0000) |
	((little >> 8) & 0xff00) | ((little << 24) & 0xff000000);
	return (big);
}

void			init_meth(t_line *line)
{
	line->method = NULL;
	line->method_position = 0;
	line->method_total = 0;
	line->opcode = 0;
	line->nb_tab = 0;
	line->nb_info = 0;
	line->info1 = NULL;
	line->info2 = NULL;
	line->info3 = NULL;
	ft_bzero(line->intfo1, 12);
	ft_bzero(line->intfo2, 12);
	ft_bzero(line->intfo3, 12);
	line->encod = 0;
	line->line_in_file = 0;
	line->next = NULL;
}