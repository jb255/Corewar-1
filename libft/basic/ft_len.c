/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:47:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/09/27 21:01:44 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_len(char const *s, char c)
{
	int		length;

	length = 0;
	while (*s != c && *s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

char		*create_space(int c)
{
	char	*str;
	int		u;

	u = -1;
	str = (char*)malloc(sizeof(char) * c + 1);
	while (c > ++u)
		str[u] = ' ';
	str[u + 1] = '\0';
	if (!str)
		return (NULL);
	return (str);
}
