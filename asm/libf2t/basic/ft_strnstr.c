/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:49:17 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/01 10:38:10 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	nlen;
	int		lastresult;

	if (*s2 == '\0')
		return ((char*)s1);
	nlen = ft_strlen(s2);
	lastresult = 1;
	while (nlen <= n && *s1 != '\0'
		&& (lastresult = ft_strncmp(s1, s2, nlen)))
	{
		n--;
		s1++;
	}
	if (lastresult != 0)
		return (NULL);
	else
		return ((char *)s1);
}
