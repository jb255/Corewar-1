/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:59:38 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/14 22:28:05 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

char	*get_x_from_position(t_env *e, int from, int at)
{
	char            *result = "";
    char            *name;
    int                index;
    char            *tmp;

    (void)e;
    if (from < 0)
        from = MEM_SIZE + from;
    index = from % MEM_SIZE;
    while (index != at % MEM_SIZE)
    {
        name = ft_sprintf("%02x", (unsigned char)tab[index % MEM_SIZE]);
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
