/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 13:33:54 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/28 13:33:56 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;
	t_list	*tmp;
	t_list	*tmp2;

	if (!f || !lst)
		return (NULL);
	tmp = (*f)(lst);
	if (!(result = ft_lstnew(tmp->content, tmp->content_size)))
		return (NULL);
	lst = lst->next;
	tmp2 = result;
	while (lst)
	{
		tmp = (*f)(lst);
		if (!(tmp2->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (NULL);
		lst = lst->next;
		tmp2 = tmp2->next;
	}
	return (result);
}
