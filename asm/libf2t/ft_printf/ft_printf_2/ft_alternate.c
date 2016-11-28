/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alternate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:49:45 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 17:59:46 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*intern_condition(char *result, T_LIST *trail, int i)
{
	char	*insert;

	insert = NULL;
	while (!ft_isalnum(result[i]) && result[i])
		i++;
	if ((trail->format == 'o' || trail->format == 'O') &&
		result[0] != '0')
		insert = ft_strdup("0");
	else if (trail->format == 'x' && ft_strcmp(result, "0"))
		insert = ft_strdup("0x");
	else if (trail->format == 'X' && ft_strcmp(result, "0"))
		insert = ft_strdup("0X");
	else if (trail->format == 'b')
		insert = ft_strdup("b");
	else if (!trail->accuracy && (trail->format == 'x' ||
				trail->format == 'X'))
	{
		free(result);
		result = ft_strnew(0);
	}
	if (insert)
		result = ft_repstr(result, i, i, insert);
	free(insert);
	return (result);
}

char			*ft_alternate(char *result, T_LIST *trail)
{
	int		i;
	char	*insert;

	i = 0;
	insert = NULL;
	if (trail->format == 'o' || trail->format == 'O' || trail->format == 'x' ||
			trail->format == 'X' || trail->format == 'b')
		result = intern_condition(result, trail, i);
	else if (trail->type == 'f')
	{
		while (!ft_isdigit(result[i]))
			i++;
		while (ft_isdigit(result[i]))
			i++;
		if (result[i] != '.')
		{
			insert = ft_strdup(".");
			result = ft_repstr(result, i, i, insert);
		}
	}
	if (insert)
		free(insert);
	return (result);
}
