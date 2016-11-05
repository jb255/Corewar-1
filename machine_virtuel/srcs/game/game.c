/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:50:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/05 04:49:40 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		jump(int code, char *status)
{
	int		jump;

	jump = 1;
	if ((code == 90 && !ft_strcmp(status, "ld")) || (code == 68 && !ft_strcmp(status, "sti")))
		return (14);
	else if (code == 64 && !ft_strcmp(status, "sti"))
		return (12);
	else if ((code == 70 && !ft_strcmp(status, "st")) || !ft_strcmp(status, "live"))
		return (10);
	else if (!ft_strcmp(status, "fork") || !ft_strcmp(status, "zjump"))
		return (6);
	else if (code == 94 && !ft_strcmp(status, "ldi"))
		return (12);
	else if (code == 58)
		return (12);
	else if (code == 54 && (!ft_strcmp(status, "add") || !ft_strcmp(status, "xor")))
		return (10);
	else if (code == 64 && (!ft_strcmp(status, "and") || !ft_strcmp(status, "xor")))
		return (16);
	else if (code == 68 && !ft_strcmp(status, "sti"))
		return (16);
	// else
	// 	vm_error("Error jump == 1");
	return (jump);
}

// void	curse_player()
// {
// 	int		x;
// 	char	*hex;
// 	char	*code;
// 	int		done;
//
// 	done = 0;
// 	x = 0;
// 	hex = malloc(sizeof(char) * 8);
// 	code = malloc(sizeof(char) * 8);
// 	hex[7] = '\0';
// 	code[2] = '\0';
// 	while (1)
// 	{
// 		if (tab2[x % MEM_SIZE] == 1)
// 		{
// 			hex[0] = tab[x % MEM_SIZE];
// 			hex[1] = tab[x % MEM_SIZE + 1];
// 			code[0] = tab[x % MEM_SIZE + 2];
// 			code[1] = tab[x % MEM_SIZE + 3];
// 			printf("%s, %s\n", status_code[instruct_tab_value(hex)], code);
// 			if (tab3[x] == '-' && !done)
// 			{
// 				tab3[x] = tab[x ];
// 				tab3[x + 1] = tab[x + 1];
// 				done = jump(ft_atoi(code), status_code[instruct_tab_value(hex)]);
// 			}
// 			x += jump(ft_atoi(code), status_code[instruct_tab_value(hex)]);
// 			usleep(70000);
// 			if (done)
// 				done -= 2;
// 		}
// 	}
// 	return ;
// }

char	*to_opcode(char c, char c1)
{
	char	*value;

	value = NULL;
	if (!(value = (char*)malloc(sizeof(char) * 3)))
		vm_error("Malloc error. to_opcode");
	value[0] = c;
	value[1] = c1;
	value[2] = '\0';
	return (value);
}

void	find_label(t_env *e, int x)
{
	char	status_code[17][8] = {"None", "live","ld","st","add","sub","and","or","xor","zjump","aff","ldi","sti","fork","lld","lldi","lfork"};
	char	*label;
	char	*size;

	label = to_opcode(tab[e->players[x].position % (MEM_SIZE * 2)], tab[(e->players[x].position + 1) % (MEM_SIZE * 2)]);
	size = to_opcode(tab[e->players[x].position + 2], tab[e->players[x].position + 3]);
	if (!ft_strcmp("00", label) && !ft_strcmp("00", size))
	{
		e->players[x].position = 0;
		return ;
	}
	mvwprintw(e->window.menu, 4+x, 90, "Test%d, %s, %s", x, status_code[instruct_tab_value(label)], size);
	int jumpx = jump(ft_atoi(size), status_code[instruct_tab_value(label)]);
	int index = 0;
	while (index < jumpx)
	{
		mvwprintw(e->window.menu, 4+x, 120+index, "%c", tab[e->players[x].position + index]);
		index++;
	}
	// e->players[x].position += jumpx;
	e->players[x].jumptodo = jumpx;
	// wrefresh(e->window.memory);
	// sleep(1);
	// printf("%d\n", e->players[x].position);
}

void	lets_play(t_env *e)
{
	// int		x;

	// x = -1;
	// while (++x < e->active_players)
	// {
	find_label(e, 0);

	// }
}
