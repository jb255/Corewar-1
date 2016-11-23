/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 00:06:22 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/20 00:06:23 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		get_method_pos(char *label_name, t_env *file)
{
	t_func	*func;

	func = file->head;
	while (func && ft_strcmp(func->label, label_name))
		func = func->next;
	if (!func)
		asm_error("An unknown error occured");
	return (func->position);
}

void	trim_args(t_env *file)
{
	t_func	*tmp_func;

	tmp_func = file->head;
	while (tmp_func)
	{
		tmp_func->label[ft_strlen(tmp_func->label) - 1] = 0;
		tmp_func = tmp_func->next;
	}
}
