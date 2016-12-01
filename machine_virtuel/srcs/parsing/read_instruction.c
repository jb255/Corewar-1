/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 09:02:53 by viko              #+#    #+#             */
/*   Updated: 2016/12/01 11:13:17 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		instruct_tab_value(char *str)
{
	int		value;

	value = -1;
	if (str[0] == '0' && str[1] > '0' && str[1] <= '9')
		value = str[1] - '0';
	else if (str[0] == '1' && str[1] == '0')
		value = 10;
	else if (str[0] == '0' && str[1] >= 'a' && str[1] <= 'f')
		value = str[1] - '0' - '0' + 10;
	return (value);
}

int		get_func_method(int jump, char **action_, char *tmp)
{
	char	status_code[17][16] = {"None", "live","ld","st","add","sub","and","or","xor","zjump","aff","ldi","sti","fork","lld","lldi","lfork"};
	int		jump_mod[17] = {0,5,7,5,5,0,8,0,8,3,0,0,7,3,0,0,0};
	int		index;

	index = 0;
	if (!jump && (index = instruct_tab_value(tmp)) != -1 && index > 0 && index < 17)
	{
		(*action_) = status_code[index];
		jump = jump_mod[index];
		/// erreur avec le 0b 64 r1 %:122 r2 ....
	}
	return (jump);
}

void	read_instruction(t_env *e, int x)
{
	char	*tmp = NULL;
	int		byte;
	char	c = 0;
	char	*action_;
	int		saut = 0;
	int		pair = 0;

	action_ = malloc(sizeof(char) * 8);
	byte = BYTE_START_CODE;
	while (byte < (int)e->players[x].size)
	{
		e->players[x].size_func = ((int)e->players[x].size - BYTE_START_CODE);
		c = e->players[x].file[byte];
		tmp = print_hexa(c, byte);
		saut = get_func_method(saut, &action_, tmp);
		printf("%s ", tmp);
		saut--;
		if (saut == 0){
			printf("\n");
			pair = 0;
		}
		byte++;
		free(tmp);
	}
	printf("\n");

}
// 0 0000 1 0001 0 0 0 1	0 0 1 0
// 0 0000 0 0000 0 0 0 1	0 0 1 1
// 1 0001 4 0100 0 1 0 1	1 0 0 0
// 0 0000 0 0000 0 0 0 0	1 0 0 0
// 0 0000 1 0001 0 0 0 1	1 0 0 1
//
// 0000 0001
// 0000 0000
// 0000 1111
// 0000 0000
// 0000 0001
//    10001
// 0x0b,0x68,0x01,0x00,0x0f,0x00,0x01
//
//
// 01 11 10 00 soit 0x78
// 0x78 puis 0x02 0x00 0x17 0x00 0x00 0x00 0x22
//
//
//
// 02 0000 0010 x 00 0000 0000 x 17 0001 0111 x 00 0000 0000 x 22 0010 0010
//
//
//
// 64 = 01 10 01 00
// 0b 64 04 ff f2 02
//
// 68 = 01 10 10 00
// 0b 68 01 00 14 00 01
