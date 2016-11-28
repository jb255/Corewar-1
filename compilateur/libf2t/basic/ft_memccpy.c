/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:35:24 by vlancien          #+#    #+#             */
/*   Updated: 2015/11/27 15:35:25 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*rdst;
	const char		*rsrc;

	rdst = dst;
	rsrc = src;
	while (n > 0 && *rsrc != c)
	{
		*rdst++ = *rsrc++;
		n--;
	}
	if (n > 0)
	{
		*rdst++ = *rsrc++;
		return ((void*)rdst);
	}
	else
		return (NULL);
}
