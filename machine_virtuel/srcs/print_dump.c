/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <jaustry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 18:02:59 by jaustry           #+#    #+#             */
/*   Updated: 2016/12/13 19:16:12 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <n_curse.h>
#include <players.h>

void	write_tab(void)
{
	int x ;

	x = 0;
	while (x < MEM_SIZE)
	{
		if (x % 64 == 0)
			ft_printf("0x%04x : ", x);
		ft_printf("%02x ", tab[x]);
		x++;
		if (x % 64 == 0)
			ft_printf("\n");
	}
}
