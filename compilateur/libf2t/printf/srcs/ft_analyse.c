/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 20:25:47 by vlancien          #+#    #+#             */
/*   Updated: 2016/09/27 21:08:17 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_arg(char c)
{
	if (ft_strchr("sSpdDioOuUxXcC", c) != 0)
		return (1);
	return (0);
}

char	ft_analyse(char const *str, t_info_str *list)
{
	int		count;

	count = 1;
	while (str[count] != '\0' && !is_arg(str[count]))
	{
		list->flag_size++;
		count++;
	}
	list->flag_size += 2;
	return (str[count]);
}
