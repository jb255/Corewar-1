/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transfer_wchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:55:43 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 17:41:38 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void				part_two(wchar_t c, int *oct_num, unsigned char **b)
{
	if (c < (1 << 16))
	{
		*oct_num = 3;
		(*b)[0] = (unsigned char)(((c >> 12)) | 0xE0);
		(*b)[1] = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		(*b)[2] = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 21))
	{
		*oct_num = 4;
		(*b)[0] = (unsigned char)(((c >> 18)) | 0xF0);
		(*b)[1] = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
		(*b)[2] = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		(*b)[3] = (unsigned char)((c & 0x3F) | 0x80);
	}
}

unsigned char			*ft_transfer_wchar(wchar_t c, int *oct_num)
{
	unsigned char *b;

	b = (unsigned char*)ft_strnew(4);
	if (c < (1 << 7))
		b[0] = (unsigned char)(c);
	else if (c < (1 << 11))
	{
		*oct_num = 2;
		b[0] = (unsigned char)((c >> 6) | 0xC0);
		b[1] = (unsigned char)((c & 0x3F) | 0x80);
	}
	else
		part_two(c, oct_num, &b);
	return (b);
}
