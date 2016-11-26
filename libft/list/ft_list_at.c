/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:16:34 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/28 17:16:35 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	if (begin_list->next == NULL && nbr >= 2)
		return (NULL);
	if (nbr == 1)
		return (begin_list);
	return (ft_list_at(begin_list->next, nbr - 1));
}
