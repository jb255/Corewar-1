/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 18:02:59 by jaustry           #+#    #+#             */
/*   Updated: 2016/12/08 18:03:01 by jaustry          ###   ########.fr       */
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
		printf("%02x ", tab[x]);
		x++;
		if (x % 64 == 0)
			printf("\n");
	}
}
