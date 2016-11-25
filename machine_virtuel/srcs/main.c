/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:59:13 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/25 09:16:09 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "n_curse.h"
#include "players.h"

void	free_fighter(t_env *e)
{
	int		x;

	x = 0;
	while (x < e->active_players)
	{
		free(e->players[x].name);
		free(e->players[x].file);
		free(e->players[x].comment);
		x++;
	}
}



int		main(int argc, char **argv)
{
	t_env *e;

	e = (t_env *)ft_memalloc(sizeof(t_env));
	if (argc < 2)
		vm_error("Need more argument!");
	parsing_arg(argv, e);
	init_curse();
	put_player(e);
	// free(e->process[0]->position);
	e->arena.cycle = CYCLE_TO_DIE;
	e->flag.pause = 0;
	if (e->flag.flag_n)
		n_curse(e);
	// free_fighter(e);
	printf("END OF THE PROGRAM\n");

	// char		*str;
	// t_type_func	test;
	//
	// str = strdup("90");
	// test = check_jump(e, hex_to_bin_quad(str));
	// printf("Size = %d\n", test.size + 2);
	// printf("%s\n", ft_itoa_base(21925245, 16));
	// printf("%d\n", hex_to_dec("FE"));
	// printf("%s\n", dec_to_hex(-1, NULL, 3));
	// printf("%s\n", to_tab(strdup("B")));
	// printf("%d %d %d %d\n", get_oct_from_str(9, 1), get_oct_from_str(9, 2), get_oct_from_str(9, 3), get_oct_from_str(9, 4));
	// printf("main_>%s\n", ft_itoa_base(-1, 16));
	// printf("main_>%ld\n", hex_to_dec("e7" , 2));
	return (0);
}
