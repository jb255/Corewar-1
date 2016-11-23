/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:59:13 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/22 06:27:16 by vlancien         ###   ########.fr       */
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

char	*to_tab(char *str)
{
	char	*result;

	result = NULL;
	if (ft_strlen(str) == 1)
	{
		result = ft_strjoin("0", to_lower(str));
		free(str);
		return (result);
	}
	return (str);
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
	e->arena.cycle = CYCLE_TO_DIE;
	e->flag.pause = 0;
	if (e->flag.flag_n)
		n_curse(e);
	free_fighter(e);
	printf("END OF THE PROGRAM\n");

	char		*str;
	t_type_func	test;

	str = strdup("90");
	test = check_jump(e, hex_to_bin_quad(str));
	printf("Size = %d\n", test.size + 2);
	printf("%s\n", ft_itoa_base(21925245, 16));
	printf("%d\n", hex_to_dec("11"));
	printf("%s\n", dec_to_hex(255, NULL, 3));
	printf("%s\n", to_tab(strdup("B")));
	// printf("main_>%ld\n", hex_to_dec("01" , 2));
	// printf("main_>%ld\n", hex_to_dec("e7" , 2));
	return (0);
}
