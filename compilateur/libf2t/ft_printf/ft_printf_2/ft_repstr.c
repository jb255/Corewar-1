/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:55:02 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 17:07:04 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*ft_repstr(char *str, int start, int end, char *to_insert)
{
	char	*res;
	int		i;
	int		j;

	if (ft_strlen(str) == 0)
		return (ft_strdup(to_insert));
	res = (char*)malloc(sizeof(char) *
		(ft_strlen(str) - (end - start) + ft_strlen(to_insert) + 1));
	ft_bzero(res, ft_strlen(str) - (end - start) + ft_strlen(to_insert) + 1);
	i = 0;
	j = 0;
	while (i < start)
	{
		res[i] = str[i];
		i++;
	}
	while (j < (int)ft_strlen(to_insert))
		res[i++] = (int)to_insert[j++];
	j = end;
	while (str[j] != 0)
		res[i++] = (int)str[j++];
	res[i] = 0;
	free(str);
	return (res);
}
