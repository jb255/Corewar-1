/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:35:42 by vlancien          #+#    #+#             */
/*   Updated: 2016/08/25 09:03:18 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*result;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	result = new;
	if (new == NULL)
		return (NULL);
	while (*s1 != '\0')
		*result++ = *s1++;
	while (*s2 != '\0')
		*result++ = *s2++;
	*result = '\0';
	return (new);
}
