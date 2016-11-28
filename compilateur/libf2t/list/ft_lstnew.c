/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:26:11 by vlancien          #+#    #+#             */
/*   Updated: 2015/12/03 16:26:58 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*liste;

	liste = (t_list*)malloc(sizeof(t_list));
	if (liste == NULL)
		return (NULL);
	if (content == NULL)
	{
		liste->content = NULL;
		liste->content_size = 0;
	}
	else
	{
		liste->content = malloc(content_size);
		if (content == NULL)
		{
			free(liste);
			return (NULL);
		}
		ft_memcpy(liste->content, content, content_size);
		liste->content_size = content_size;
	}
	liste->next = NULL;
	return (liste);
}
