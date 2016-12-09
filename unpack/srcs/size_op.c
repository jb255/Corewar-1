/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:21:41 by viko              #+#    #+#             */
/*   Updated: 2016/12/09 17:43:03 by viko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

char	*get_x(t_file *cor, int from, int at)
{
	char			*result = "";
	char			*name;
	int				index;

	index = from;
	while (index != at)
	{
		name = ft_sprintf("%02x", ((signed int)cor->content[index]));
		result = ft_strjoin(result, name);
		index++;
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
