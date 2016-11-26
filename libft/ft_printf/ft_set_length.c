/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 11:45:29 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 10:58:29 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*set_x_length(T_LIST *trail, char *result)
{
	char	*insert;

	if (ft_strlen(result) && trail->accuracy > (int)ft_strlen(result))
	{
		insert = ft_strset(ft_strnew(trail->accuracy - ft_strlen(result)),
				trail->accuracy - ft_strlen(result), '0');
		result = ft_repstr(result, 0, 0, insert);
		free(insert);
	}
	return (result);
}

static int		get_slen(char *wsize, int acc)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (wsize[i] && ret + wsize[i] <= acc)
	{
		ret += wsize[i];
		i++;
	}
	return (ret);
}

static char		*set_ds_length(T_LIST *trail, char *result, int i, int j)
{
	char	*insert;

	insert = ft_strset(ft_strnew(i), i, '0');
	if (trail->type == 'd' && i > 0)
		result = ft_repstr(result, j, j, insert);
	free(insert);
	if (trail->type == 'S' && trail->accuracy != -1)
		result[get_slen(trail->w_size, trail->accuracy)] = 0;
	else if (trail->type == 's')
		result[trail->accuracy] = 0;
	return (result);
}

char			*ft_set_length(T_LIST *trail, char *result)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!ft_strcmp(result, "0") && !trail->accuracy && !trail->alternate)
		return (ft_strnew(1));
	if (trail->format == 'x' || trail->format == 'X' || trail->type == 'p')
		return (result = set_x_length(trail, result));
	while (result[++j] != 0)
		if (ft_isdigit(result[j]))
			i++;
	i = trail->accuracy - i;
	j = 0;
	while (!ft_isdigit(result[j]) && result[j] != 0)
		j++;
	if (trail->type == 'd' || trail->type == 'S' || trail->type == 's')
		result = set_ds_length(trail, result, i, j);
	return (result);
}
