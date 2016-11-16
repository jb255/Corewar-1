/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_reg_chr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 13:55:44 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/13 13:58:48 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_reg_chr(const char *s, int c)
{
	char	wanted;
	char	*tmp;
	int		i;
	int		j_dash;

	i = -1;
	wanted = (char)c;
	tmp = (char *)s;
	while (tmp[++i] != 0)
	{
		if (tmp[i] == '-')
		{
			j_dash = tmp[i - 1];
			while (++j_dash < tmp[i + 1])
				if (j_dash == wanted)
					return (&(tmp[i]));
		}
		else if (tmp[i] == wanted)
			return (&(tmp[i]));
	}
	return (NULL);
}
