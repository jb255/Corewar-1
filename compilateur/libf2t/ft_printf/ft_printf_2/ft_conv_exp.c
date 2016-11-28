/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:51:43 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/03 17:18:51 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	init_inum(int *i, long double *number)
{
	while (*number >= 10.0 || *number <= -10.0)
	{
		*number /= 10.0;
		(*i)++;
	}
	while (*number < 1.0 && *number > -1.0)
	{
		*number *= 10.0;
		(*i)--;
	}
}

static char	*condition(char *res)
{
	char	*insert;

	insert = ft_strdup("+");
	res = ft_repstr(res, 0, 0, insert);
	free(insert);
	return (res);
}

char		*ft_conv_exp(long double number, T_LIST *trail)
{
	int		i;
	char	*res;
	char	*insert;

	i = 0;
	init_inum(&i, &number);
	res = ft_itoa(i);
	if (i < 10 && i > -10)
	{
		insert = ft_strdup("0");
		res = ft_repstr(res, i < 0 ? 1 : 0, i < 0 ? 1 : 0, insert);
		free(insert);
	}
	if (i >= 0)
		res = condition(res);
	insert = ft_strdup("e");
	res = ft_repstr(res, 0, 0, insert);
	free(insert);
	insert = ft_conv_float(number, trail->accuracy > 0 ? trail->accuracy : 6);
	res = ft_repstr(res, 0, 0, insert);
	free(insert);
	return (res);
}
