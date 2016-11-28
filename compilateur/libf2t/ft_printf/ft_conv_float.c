/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:51:50 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 12:47:41 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		ft_is_neg(int *k, long double *number, char **final)
{
	if (*number < 0)
	{
		*number = *number * -1;
		*k = *k + 1;
		(*final)[0] = '-';
	}
}

static char		*after_coma(char *final, long double to_print, int acc, int k)
{
	while (acc-- > 0)
	{
		to_print *= 10;
		final[k++] = (intmax_t)to_print + 48;
		to_print = to_print - (intmax_t)to_print;
	}
	return (final);
}

char			*ft_conv_float(long double to_print, int acc)
{
	char		*final;
	int			k;
	long double	i;

	i = 1.0;
	k = 0;
	final = ft_strnew(310);
	ft_is_neg(&k, &to_print, &final);
	ft_round(&to_print, acc);
	while (i < to_print)
		i *= 10;
	while ((i = i / 10) >= 1)
	{
		final[k++] = (int)(to_print / i) + 48;
		to_print = (long double)((intmax_t)to_print % (intmax_t)i) + to_print -
			(intmax_t)to_print;
	}
	if (k == 0)
		final[k++] = '0';
	final[k++] = (acc > 0) ? '.' : 0;
	final = after_coma(final, to_print, acc, k);
	return (final);
}
