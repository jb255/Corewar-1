/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:38:21 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/01 10:38:23 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char const *slst;

	slst = NULL;
	if (s == NULL)
		return (NULL);
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (*s == '\0')
		return (ft_strnew(0));
	slst = s + ft_strlen(s) - 1;
	while (*slst == ' ' || *slst == '\t' || *slst == '\n')
		slst--;
	return (ft_strsub(s, 0, slst - s + 1));
}
