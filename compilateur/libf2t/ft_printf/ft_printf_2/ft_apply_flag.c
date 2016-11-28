/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:49:55 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 10:30:49 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_apply_flag(char *result, T_LIST *trail)
{
	char	t;
	char	*insert;

	t = trail->format;
	if ((trail->type == 'd' || trail->type == 'f') && (trail->plus ||
				trail->space || result[0] == '-'))
	{
		if (trail->plus && ft_isdigit(result[0]) && (trail->is_signed ||
			trail->type == 'f'))
		{
			insert = ft_strdup("+");
			result = ft_repstr(result, 0, 0, insert);
			free(insert);
		}
		else if (trail->space && ft_isdigit(result[0]) && trail->is_signed)
		{
			insert = ft_strdup(" ");
			result = ft_repstr(result, 0, 0, insert);
			free(insert);
		}
	}
	return (result);
}
