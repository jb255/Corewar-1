/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:53:42 by vlancien          #+#    #+#             */
/*   Updated: 2015/11/26 18:53:43 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *src;

	if (s == NULL)
		return (NULL);
	src = (unsigned char*)s;
	while (n > 0 && *src != (unsigned char)c)
	{
		n--;
		src++;
	}
	if (n == 0)
		return (NULL);
	else
		return (src);
}
