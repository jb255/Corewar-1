/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_accuracy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:52:26 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 15:54:54 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_get_accuracy(char *format, int *j, T_LIST *trail)
{
	int		i;
	char	*str;

	(*j)++;
	i = *j;
	while (format[*j] && (ft_isdigit(format[*j]) || format[*j] == '*'))
	{
		if (format[*j] == '*')
		{
			trail->accuracy = -10;
			return ;
		}
		(*j)++;
	}
	str = ft_strsub(format, i, *j - i);
	trail->accuracy = ft_atoi(str);
	free(str);
	if (i == *j)
		trail->accuracy = 0;
	(*j) -= 1;
}
