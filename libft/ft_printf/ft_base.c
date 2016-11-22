/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 13:03:06 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 14:40:09 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#define C_LONG_MAX "9223372036854775807"
#define C_LONG_MIN "-9223372036854775808"

static void		ft_isneg(intmax_t *num, int *k, char *final)
{
	if (*num < 0)
	{
		*num = -(*num);
		*k = 1;
		final[0] = '-';
	}
}

static void		ft_make_base(int *base)
{
	if (*base == 'o' || *base == 'O')
		*base = 8;
	if (*base == 'x' || *base == 'X')
		*base = 16;
	if (*base == 'b')
		*base = 2;
	if (*base == 'd' || *base == 'D' || *base == 'i' || *base == 'u' ||
		*base == 'U')
		*base = 10;
}

char			*ft_base(intmax_t num, int base)
{
	char			*final;
	int				k;
	intmax_t		i;
	char			alpha[17];

	ft_make_base(&base);
	i = 1;
	k = 0;
	if (num == LONG_MAX || num == LONG_MIN)
		return (ft_strdup((num == LONG_MAX) ? C_LONG_MAX : C_LONG_MIN));
	ft_strcpy(alpha, "0123456789abcdef");
	ft_bzero(final = (char*)malloc(sizeof(char) * 200), 200);
	ft_isneg(&num, &k, final);
	while (i <= num / base)
		i = i * base;
	while (i > 0)
	{
		final[k++] = alpha[(num / i)];
		num = num % i;
		i /= base;
	}
	final[k] = 0;
	return (final);
}

static char		*return_good_base(uintmax_t num, int base)
{
	if (base == 8 && num == ULONG_MAX)
		return (ft_strdup("1777777777777777777777"));
	else if (base == 16)
		return (ft_strdup("ffffffffffffffff"));
	return (ft_strdup(num == ULONG_MAX ? "18446744073709551615" :
			"1000000000000000000000"));
}

char			*ft_ubase(uintmax_t num, int base)
{
	char					*final;
	int						k;
	uintmax_t				i;
	char					alpha[17];

	ft_make_base(&base);
	i = 1;
	k = 0;
	if (num == ULONG_MAX || num == ULONG_MAX / 2 + 1)
		return (return_good_base(num, base));
	ft_strcpy(alpha, "0123456789abcdef");
	ft_bzero(final = (char*)malloc(sizeof(char) * 200), 200);
	while (i <= num / base)
		i = i * base;
	while (i > 0)
	{
		final[k++] = alpha[(num / i)];
		num = num % i;
		i /= base;
	}
	final[k] = 0;
	return (final);
}
