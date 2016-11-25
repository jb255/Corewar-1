/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 21:59:31 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/25 08:39:27 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

int		get_oct_from_str(int id, int nb)
{
	int		result;
	char	*code;

	result = 0;
	code = dec_to_hex(id, NULL, intlen(id, 10));
	if (ft_strlen(code) != 8)
		return (0);
	if (nb == 2)
		code += 2;
	if (nb == 3)
		code += 4;
	if (nb == 4)
		code += 6;
	code[2] = '\0';
	result = ft_atoi(code);
	result = hex_to_dec(code);
	return (result);
}

void	name_process(t_env *e, char	*name)
{
	int		x;

	x = 0;
	while (x < e->active_players)
	{
		if (!ft_strcmp(name, dec_to_hex(-(e->players[x].id_player+1), NULL, 3)))
			printf("LIVE FOR %s\n", e->players[x].name);
		x++;
	}
}
void	live_func(t_env *e, int xproc, t_type_func list)
{
	int		index;
	char	*name;

	index = 1;
	(void)list;
	unsigned int	x;
	char		*result = "";
	while (index < 5)
	{
		x = tab[e->process[xproc]->position + index];
		name = dec_to_hex(x, NULL, intlen(x, 10));
		result = ft_strjoin(result, strdup(name));
		index++;
	}
	name_process(e, result);
	// printf("{%s}-{%s}\n", result, dec_to_hex(-1, NULL, 3));
	//
	// if (list.func == 1 && ft_strcmp(result, dec_to_hex(-(e->process[xproc]->id_player+1), NULL, 3)) == 0)
	// 	printf("LIVE FOR %s - %d\n", e->players[e->process[xproc]->id_player].name, e->process[xproc]->position);
	free(result);
	nodelay(stdscr, 1);
	getch();
}
