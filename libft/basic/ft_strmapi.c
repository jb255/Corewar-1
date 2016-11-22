/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:36:03 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/01 10:36:07 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh;
	char			*result;
	unsigned int	count;

	count = 0;
	if (s == NULL)
		return (NULL);
	fresh = ft_strnew(ft_strlen(s + 1));
	if (fresh == NULL)
		return (NULL);
	result = fresh;
	while (s[count] != '\0')
	{
		fresh[count] = f(count, s[count]);
		count++;
	}
	fresh[count] = '\0';
	return (result);
}
