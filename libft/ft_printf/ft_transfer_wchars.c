/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transfer_wchars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:55:47 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 18:06:52 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_transfer_wchars(wchar_t *wstr, T_LIST *trail, unsigned char **p)
{
	unsigned char	*result;
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	int				i;

	result = (unsigned char*)ft_strnew(0);
	i = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	while (wstr[i] != 0)
	{
		free(tmp2);
		tmp2 = ft_transfer_wchar(wstr[i], &(trail->oct_num));
		trail->w_size[i] = trail->oct_num;
		tmp1 = result;
		result = (unsigned char*)ft_strnew(ft_strlen((char*)result) +
				ft_strlen((char*)tmp2));
		result = (unsigned char*)ft_strcpy((char*)result, (char*)tmp1);
		result = (unsigned char*)ft_strcat((char*)result, (char*)tmp2);
		i++;
		free(tmp1);
	}
	*p = tmp2;
	return ((char*)result);
}
