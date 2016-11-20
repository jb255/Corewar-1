/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_fmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:51:32 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/03 15:51:33 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_check_fmt(char const *fmt)
{
	int		i;

	i = 0;
	while (ft_is_valid(fmt[i]) && !ft_is_format(fmt[i]) && fmt[i])
		++i;
	if (!ft_is_valid(fmt[i]))
		return (1);
	else if (ft_is_format(fmt[i]) || !fmt[i])
		return (2);
	else
		return (0);
}
