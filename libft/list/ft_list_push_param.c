/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 17:16:12 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/28 17:16:13 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_push_param(int ac, char **av)
{
	t_list		*list;

	if (ac == 1)
		return (NULL);
	else
	{
		list = ft_create_elem(av[--ac]);
		while (0 < (ac - 1))
		{
			ac--;
			ft_list_push_back(&list, av[ac]++);
		}
	}
	return (list);
}
