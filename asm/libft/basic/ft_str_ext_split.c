/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_ext_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:43:28 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/23 18:05:28 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	count_words(char *str, char *ext)
{
	int		i;
	int		w;

	w = 0;
	i = 0;
	while (str[i] != 0 && str[i] != '\200')
	{
		if (ft_strchr(ext, str[i]) && i != 0 && !ft_strchr(ext, str[i - 1]))
			w += 1;
		i += 1;
	}
	return (w + 1);
}

static void	fill(char **actual, char **iter, char *ext)
{
	char	*tmp;
	int		i;
	char	*end;

	i = 0;
	end = *iter + ft_strlen(*iter);
	while (ext[i] != 0)
	{
		tmp = ft_strchr(*iter, ext[i]);
		if (tmp && tmp - *iter < end - *iter)
			end = tmp;
		i += 1;
	}
	if (!*end)
		*actual = ft_strdup(*iter);
	else
	{
		*actual = ft_strnew(end - *iter + 1);
		ft_strncpy(*actual, *iter, end - *iter);
		*iter = end;
		while (ft_strchr(ext, **iter))
			*iter += 1;
	}
}

char		**ft_str_ext_split(char *str, char *ext)
{
	char	**res;
	int		nb_w;
	int		k;
	char	*tmp;

	if (str == NULL || ft_strlen(str) == 0)
		return (NULL);
	nb_w = count_words(str, ext);
	res = (char **)malloc(sizeof(char *) * (nb_w + 1));
	k = 0;
	while (k < nb_w)
		res[k++] = NULL;
	tmp = str;
	k = 0;
	while (k < nb_w)
	{
		fill(&(res[k]), &tmp, ext);
		k += 1;
	}
	res[k] = NULL;
	return (res);
}
