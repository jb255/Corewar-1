/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:58:56 by vlancien          #+#    #+#             */
/*   Updated: 2015/11/27 15:58:57 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char *ssrc;
	char *sdst;

	ssrc = (char*)src;
	sdst = (char*)dest;
	if (ssrc < sdst)
	{
		ssrc = ssrc + len - 1;
		sdst = sdst + len - 1;
		while (len > 0)
		{
			*sdst-- = *ssrc--;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*sdst++ = *ssrc++;
			len--;
		}
	}
	return (dest);
}
