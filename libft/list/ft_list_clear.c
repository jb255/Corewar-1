/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:16:41 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/28 17:16:42 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_destroy(t_list *list)
{
	if (list)
		free(list);
}

void	ft_list_clear(t_list **begin_list)
{
	ft_destroy(*begin_list);
	*begin_list = NULL;
}
