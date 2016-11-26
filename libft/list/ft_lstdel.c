/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 18:15:04 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/03 18:15:05 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*temp;
	t_list		*next;

	if (*alst == NULL || alst == NULL)
		return ;
	else
	{
		temp = *alst;
		while (temp)
		{
			next = temp->next;
			ft_lstdelone(&temp, del);
			temp = next;
		}
		*alst = NULL;
	}
}
