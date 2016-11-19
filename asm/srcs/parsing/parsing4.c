/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:43:50 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/19 03:01:58 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_single_label(t_line *line, t_func *func, int nb_info, t_env *env)
{
	char	*info;

	if (nb_info == 1 || nb_info == 2)
		info = nb_info == 1 ? line->info1 : line->info2;
	else
		info = line->info3;
	while (func != NULL && info && ft_strcmp(func->label, info + 2))
		func = func->next;
	if (func == NULL)
	{
		printf("Call to undefined label \"%s\" at line %d\n", info + 2, line->line_in_file);
		exit (-1);
	}
	if (nb_info == 1)
		line->intfo1[1] = get_method_pos(info + 2, env) - line->method_position;
	if (nb_info == 2)
		line->intfo2[1] = get_method_pos(info + 2, env) - line->method_position;
	if (nb_info == 3)
		line->intfo3[1] = get_method_pos(info + 2, env) - line->method_position;
}

int		verify_comma_continuity(char *str, int line)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (((i == 0 || i == ft_strlen(str) - 1) && str[i] == ',') || (i != 0 && str[i] == ',' && str[i - 1] == ','))
		{
			printf("Syntax error at line %d, trailing or double comma\n", line);
			exit(-1);
		}
		i += 1;
	}
	return (1);
}
