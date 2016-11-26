/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:38:53 by vlancien          #+#    #+#             */
/*   Updated: 2015/11/26 16:38:55 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_pos;

	last_pos = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			last_pos = (char*)s;
		s++;
	}
	if (*s == c)
		return ((char*)s);
	else
		return (last_pos);
}
