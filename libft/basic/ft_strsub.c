/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:38:15 by vlancien          #+#    #+#             */
/*   Updated: 2016/02/16 16:12:07 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t			size;
	char			*result;

	if (s == NULL)
		return (NULL);
	result = ft_strnew(len);
	if (result == NULL)
		return (NULL);
	s += start;
	size = 0;
	while (size < len)
	{
		result[size] = s[size];
		size++;
	}
	result[size++] = '\0';
	return (result);
}
