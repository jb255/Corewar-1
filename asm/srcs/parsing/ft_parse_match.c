/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:58:47 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/15 19:13:55 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static char	*ft_get_char_class(char **str)
{
	char	*class;
	int		size;

	size = ft_strlen(*str) - ft_strlen(ft_strchr(*str, ']')) - 1;
	class = ft_strnew(size + 1);
	ft_strncpy(class + 1, (*str + 1), size);
	*str += size + 1;
	class[0] = *(*str + 1) == '+' ? 1 : 0;
	if (class[0])
		*str += 1;
	return (class);
}

static int	go_forward_char_class(char **tmpb, char **tmpa)
{
	char	*class;

	class = NULL;
	class = ft_get_char_class(tmpb);
	if (!ft_str_reg_chr(class + 1, **tmpa))
	{
		free(class);
		return (0);
	}
	(*tmpa)++;
	while (class[0] && ft_str_reg_chr(class + 1, **tmpa))
		++(*tmpa);
	free(class);
	return (1);
}

int			ft_parse_match(char *regex, char *string)
{
	char	*tmpa;
	char	*tmpb;

	tmpa = string;
	tmpb = regex;
	while (*tmpb != 0 || *tmpa != 0)
	{
		if (*tmpb == '[')
		{
			if (go_forward_char_class(&tmpb, &tmpa) == 0)
				return (0);
		}
		else if (*tmpb == '*')
		{
			while (*tmpa && !ft_parse_match(tmpb + 1, tmpa))
				++tmpa;
			return (*tmpa || !*(tmpb + 1) ? 1 : 0);
		}
		else if (*tmpb != *tmpa)
			return (0);
		else if (*tmpa)
			++tmpa;
		++tmpb;
	}
	return (1);
}
