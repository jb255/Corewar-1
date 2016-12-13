/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:21:41 by viko              #+#    #+#             */
/*   Updated: 2016/12/12 14:09:26 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

int		writememnb(int nb, int first)
{
	if (first && nb < 16)
		write(1, "0", 1);
	if (nb < 10)
		ft_putchar(nb + 48);
	else if (nb >= 10 && nb < 16)
		ft_putchar(nb + 55);
	else
	{
		writememnb(nb / 16, 0);
		writememnb(nb % 16, 0);
	}
	return (0);
}

char	*get_x(t_file *cor, int from, int at)
{
	char			*result;
	char			*name;
	int				index;
	char			*tmp;

	result = "";
	index = from;
	while (index != at)
	{
		name = ft_sprintf("%02x", (unsigned char)cor->content[index]);
		tmp = result;
		result = ft_strjoin(result, name);
		index++;
		if (ft_strlen(tmp) != 0)
			free(tmp);
		free(name);
	}
	return (result);
}

int		todec(char *str)
{
	int		result;

	result = hex_to_dec(str);
	free(str);
	return (result);
}
