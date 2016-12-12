/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hextodec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 20:06:22 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/12 13:52:56 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

unsigned int	hex_to_dec(const char *str)
{
	unsigned int	total;
	int				i;

	total = 0;
	i = 0;
	while (0 < str[i] && str[i] < 33)
		i++;
	while ((str[i] >= '0' && str[i] <= '9') ||
			(str[i] >= 'A' && str[i] <= 'F') ||
			(str[i] >= 'a' && str[i] <= 'f'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			total = (total * 16) + (str[i++] - '0');
		if (str[i] >= 'A' && str[i] <= 'F')
			total = (total * 16) + (str[i++] - 'A' + 10);
		if (str[i] >= 'a' && str[i] <= 'f')
			total = (total * 16) + (str[i++] - 'a' + 10);
	}
	return (total);
}

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
