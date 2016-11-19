/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 17:50:40 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 03:41:28 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "g_variable.h"

int		jump(int code, char *status)
{
	int		jump;

	jump = 1;
	if ((code == 90 && !ft_strcmp(status, "ld")) || (code == 68 && !ft_strcmp(status, "sti")))
		return (14);
	else if (!ft_strcmp(status, "ld"))
		return (10);
	else if (code == 64 && !ft_strcmp(status, "sti"))
		return (12);
	else if ((code == 70 && !ft_strcmp(status, "st")) || !ft_strcmp(status, "live"))
		return (10);
	else if (code == 50 && !ft_strcmp(status, "st"))
		return (8);
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
	else
		return (2);
	// vm_error("Error jump == 1");
	return (jump);
}

// 10 01 00 00
// 90
// dircode{2},
// 02 90 ff ff ff fa 03

// 01 Registre, Suivie d’un octet (le numéro de registre)
// 10 Direct, Suivie de DIR_SIZE octets (la valeur directement)
// 11 Indirect, Suivie de IND_SIZE octets (la valeur de l’indirection)

// # define REG_CODE				1
// # define DIR_CODE				2
// # define IND_CODE				3

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
	int		wait_time[17] = {0, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};
	char	*label;
	char	*size;
	int		jumpx;
	int 	index;
	int		func;

	label = to_opcode(tab[e->process[x]->position % ((MEM_SIZE))], tab[(e->process[x]->position + 1) % ((MEM_SIZE))]);
	func = instruct_tab_value(label);
	size = to_opcode(tab[e->process[x]->position + 2], tab[e->process[x]->position + 3]);
	jumpx = jump(ft_atoi(size), g_status_code[func]);
	
	index = 0;
	while (index < jumpx)
	{
		mvwprintw(e->window.menu, 4 + x, 120 + index, "%c", tab[e->process[x]->position + index]);
		index++;
	}
	mvwprintw(e->window.menu, 4 + x, 90, "Test%d, %s, %s, pos.%d label{%s}   ", jumpx, g_status_code[func], size, e->process[x]->position, label);
	wrefresh(e->window.menu);
	e->process[x]->jumptodo = jumpx;
	if (func == -1 && e->process[x]->wait_time != 2)
		e->process[x]->wait_time = 1;
	else if (e->process[x]->wait_time <= 1 && func)
		e->process[x]->wait_time = wait_time[func] / 2;
	else
		e->process[x]->wait_time--;
}
