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
	while (func != NULL && info && ft_strcmp(func->label, info + (info[0] == '%' ? 2 : 1)))
		func = func->next;
	if (func == NULL)
	{
		ft_printf("Call to undefined label \"%s\" at line %d\n", info + 2,
				line->line_in_file);
		exit(-1);
	}
	if (nb_info == 1)
		line->intfo1[1] = get_method_pos(info + (info[0] == '%' ? 2 : 1), env) - line->method_position;
	if (nb_info == 2)
		line->intfo2[1] = get_method_pos(info + (info[0] == '%' ? 2 : 1), env) - line->method_position;
	if (nb_info == 3)
		line->intfo3[1] = get_method_pos(info + (info[0] == '%' ? 2 : 1), env) - line->method_position;
}

int		verify_comma_continuity(char *str, int line)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (((i == 0 || i == (int)ft_strlen(str) - 1) && str[i] == ',') ||
			(i != 0 && str[i] == ',' && str[i - 1] == ','))
		{
			ft_printf("Syntax error at line %d, trailing or double comma\n", line);
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
	printf("On a info = %s, et se code sur %d octets\n", tmp_line->info1 ? tmp_line->info1 : "NULL", tmp_line->intfo1[2]);
	if (tmp_line->info2)
		tmp_line->intfo2[2] = get_byte_len(tmp_line->nb_tab,
				tmp_line->info2, 2);
	if (tmp_line->info3)
		tmp_line->intfo3[2] = get_byte_len(tmp_line->nb_tab,
				tmp_line->info3, 3);
}

void	inside_loop_epur(int cpt[], char *str)
{
	while (str[cpt[1]] && (str[cpt[1]] == ' ' || str[cpt[1]] == '\t'))
	{
		cpt[3] = 1;
		cpt[1]++;
	}
}

int		epur_str(char *str)
{
	int		cpt[4];

	ft_bzero(cpt, 16);
	while (str[cpt[1]] && (str[cpt[1]] == ' ' || str[cpt[1]] == '\t'))
		cpt[1]++;
	while (str[cpt[1]])
	{
		if (str[cpt[1]] != ' ' && str[cpt[1]] != '\t')
		{
			str[cpt[2]] = str[cpt[1]];
			cpt[2]++;
			cpt[1]++;
		}
		inside_loop_epur(cpt, str);
		if ((cpt[3] == 1) && str[cpt[1]])
		{
			cpt[3] = 0;
			str[cpt[2]] = ' ';
			cpt[2]++;
			cpt[0]++;
		}
	}
	str[cpt[2]] = '\0';
	return (cpt[0]);
}
