/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 02:28:03 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/18 22:10:42 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		intlen(int nb, int base)
{
	int nbr;

	nbr = 1;
	while (nb /= base)
		nbr++;
	return (nbr);
}

char	*get_result(char *result, unsigned int new, int base, int size)
{
	while (new)
	{
		if (new % base > 9)
			result[--size] = new % base + 'A' - 10;
		else
			result[--size] = new % base + '0';
		new = new / base;
	}
	return (result);
}

char	*ft_itoa_base(int value, int base)
{
	unsigned int	new;
	int				size;
	char			*result;

	new = value;
	if (value == 0)
		return (ft_strdup("0"));
	size = intlen(value, base);
	if (value < 0)
	{
		new = -value;
		size++;
	}
	result = malloc(sizeof(char) * size + 1);
	result[size] = '\0';
	result = get_result(result, new, base, size);
	if (value < 0 && base == 10)
		result[0] = '-';
	else if (value < 0)
		result++;
	return (result);
}
