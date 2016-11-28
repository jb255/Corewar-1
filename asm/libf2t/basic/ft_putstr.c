/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:34:45 by vlancien          #+#    #+#             */
/*   Updated: 2016/08/15 15:51:59 by viko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	while (*s != '\0')
	{
		ft_putchar(*s);
		s++;
	}
}

void	ft_putstr_char(char c, int nb)
{
	if (nb <= 0)
		return ;
	while (nb != 0)
	{
		ft_putchar(c);
		nb--;
	}
}
