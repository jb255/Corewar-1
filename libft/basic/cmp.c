/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:38:15 by vlancien          #+#    #+#             */
/*   Updated: 2016/05/31 04:36:52 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		cmp(const char *cs, const char *ct)
{
	unsigned char c1;
	unsigned char c2;

	while (1)
	{
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return (c1 < c2 ? -1 : 1);
		if (!c1)
			break ;
	}
	return (0);
}
