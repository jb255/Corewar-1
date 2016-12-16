/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa_to_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 10:37:58 by viko              #+#    #+#             */
/*   Updated: 2016/12/16 02:05:16 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char			*binary_get_code(int c)
{
	char	*list[16];

	list[0] = "0000";
	list[1] = "0001";
	list[2] = "0010";
	list[3] = "0011";
	list[4] = "0100";
	list[5] = "0101";
	list[6] = "0110";
	list[7] = "0111";
	list[8] = "1000";
	list[9] = "1001";
	list[10] = "1010";
	list[11] = "1011";
	list[12] = "1100";
	list[13] = "1101";
	list[14] = "1110";
	list[15] = "1111";
	return (list[c]);
}

char			*hex_to_bin_quad(char *str_1)
{
	char		*op[2];
	int			i;

	i = 0;
	while (*str_1 != '\0')
	{
		if (*str_1 >= '0' && *str_1 <= '9')
			op[i] = binary_get_code(*str_1 - '0');
		if (*str_1 >= 'A' && *str_1 <= 'F')
			op[i] = binary_get_code(10 + *str_1 - 'A');
		if (*str_1 >= 'a' && *str_1 <= 'f')
		{
			*str_1 = 10 + *str_1 - 'a';
			op[i] = binary_get_code(*str_1);
		}
		str_1++;
		i++;
	}
	return (ft_strjoin(op[0], op[1]));
}
