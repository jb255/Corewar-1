/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:59:38 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/13 18:53:15 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

char	*get_x_from_position(t_env *e, int from, int at)
{
	char			*result = "";
	char			*name;
	int				index;

	(void)e;
	if (from < 0)
		from = MEM_SIZE + from;
	index = from;
	while (index != at)
	{
		name = ft_sprintf("%02x", (unsigned char)tab[index % MEM_SIZE]);
		result = ft_strjoin(result, name);
		index++;
		if (index == MEM_SIZE)
			index = 0;
		free(name);
	}
	return (result);
}
