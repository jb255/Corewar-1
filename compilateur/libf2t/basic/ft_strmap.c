/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:35:55 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/01 10:35:58 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char		*fresh;
	char		*result;

	if (s == NULL)
		return (NULL);
	fresh = ft_strnew(ft_strlen(s + 1));
	if (fresh == NULL)
		return (NULL);
	result = fresh;
	while (*s != '\0')
	{
		*fresh = f(*s);
		s++;
		fresh++;
	}
	*fresh = '\0';
	return (result);
}
