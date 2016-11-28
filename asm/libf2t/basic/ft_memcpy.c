/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:54:59 by vlancien          #+#    #+#             */
/*   Updated: 2015/11/27 14:55:01 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*rdst;
	const char		*rsrc;

	rdst = dst;
	rsrc = src;
	while (n > 0)
	{
		*rdst++ = *rsrc++;
		n--;
	}
	return (dst);
}
