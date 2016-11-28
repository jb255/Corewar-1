/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:35:30 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/01 10:35:37 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int		count;

	count = 0;
	if (s != NULL && f != NULL)
	{
		while (s[count] != '\0')
		{
			f(count, &s[count]);
			count++;
		}
	}
}
