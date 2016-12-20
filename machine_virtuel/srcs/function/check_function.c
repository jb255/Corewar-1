/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:59:38 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/20 16:29:13 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

void	update_xy(int *from, int *at)
{
	if (*at < 0)
		*at = MEM_SIZE + *at;
	if (*from < 0)
		*from = MEM_SIZE + *from;
}

char	*get_x(int from, int at)
{
	char	*result;
	char	*name;
	char	*tmp;
	int		index;

	result = "";
	update_xy(&from, &at);
	index = from % MEM_SIZE;
	while (index != at % MEM_SIZE)
	{
		name = ft_sprintf("%02x", (unsigned char)g_tab[index % MEM_SIZE]);
		tmp = result;
		result = ft_strjoin(result, name);
		index++;
		if (index == MEM_SIZE)
			index = 0;
		if (ft_strlen(tmp) > 0)
			free(tmp);
		free(name);
	}
	return (result);
}

int		to_int_getx(char *str)
{
	int		nb;

	nb = hex_to_dec(str);
	free(str);
	return (nb);
}
