/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:52:13 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/04 15:40:37 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_free_list(T_LIST **start)
{
	if ((*start) && (*start)->next != NULL)
		ft_free_list(&((*start)->next));
	if (*start && (*start)->w_size)
		free((*start)->w_size);
	if (*start)
		free(*start);
}
