/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 19:37:53 by vlancien          #+#    #+#             */
/*   Updated: 2015/11/27 19:37:54 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cm1;
	unsigned char	*cm2;

	cm1 = (unsigned char*)s1;
	cm2 = (unsigned char*)s2;
	while (n > 0 && *cm1 == *cm2)
	{
		n--;
		cm1++;
		cm2++;
	}
	if (n == 0)
		return (0);
	else
		return (*cm1 - *cm2);
}
