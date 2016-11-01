/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_to_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 10:37:58 by viko              #+#    #+#             */
/*   Updated: 2016/11/01 16:03:29 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	binary_get_code(int c)
{
	char *list[] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101",
	"1110","1111"};
	printf("%s ", list[c]);
}

void	hex_to_bin_quad(char *str_1)
{

	while (*str_1)
	{
		if (*str_1 >= '0' && *str_1 <= '9')
			binary_get_code(*str_1 - '0');
		if (*str_1 >= 'A' && *str_1 <= 'F')
			binary_get_code(10 + *str_1 - 'A');
		if (*str_1 >= 'a' && *str_1 <= 'f')
			binary_get_code(*str_1 = 10 + *str_1 - 'a');
		str_1++;
	}
	// printf("\n");
}
