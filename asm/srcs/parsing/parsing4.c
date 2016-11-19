/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:43:50 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/19 03:40:39 by mlevieux         ###   ########.fr       */
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
		printf("Call to undefined label \"%s\" at line %d\n", info + 2,
				line->line_in_file);
		exit(-1);
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
		if (((i == 0 || i == ft_strlen(str) - 1) && str[i] == ',') ||
			(i != 0 && str[i] == ',' && str[i - 1] == ','))
		{
			printf("Syntax error at line %d, trailing or double comma\n", line);
			exit(-1);
		}
		i += 1;
	}
	return (1);
}

void	fill_intfo(t_line *tmp_line)
{
	if (tmp_line->info1)
		tmp_line->intfo1[2] = get_byte_len(tmp_line->nb_tab,
				tmp_line->info1, 1);
	if (tmp_line->info2)
		tmp_line->intfo2[2] = get_byte_len(tmp_line->nb_tab,
				tmp_line->info2, 2);
	if (tmp_line->info3)
		tmp_line->intfo3[2] = get_byte_len(tmp_line->nb_tab,
				tmp_line->info3, 3);
}

void	trim_args(t_env *file)
{
	t_func	*tmp_func;
	t_line	*tmp_line;

	tmp_func = file->head;
	while (tmp_func)
	{
		tmp_func->label[ft_strlen(tmp_func->label) - 1] = 0;
		tmp_func = tmp_func->next;
	}
}
