/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:57:55 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 04:46:33 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		labels_are_defined(t_env *file)
{
	t_func	*taf;
	t_func	*tbf;
	t_line	*tl;

	taf = file->head;
	while (taf != NULL)
	{
		tl = taf->line;
		while (tl != NULL)
		{
			if (tl->info1 && ft_parse_match("*:[a-z0-9_]+", tl->info1 + 1))
				check_single_label(tl, tbf = file->head, 1, file);
			if (tl->info2 && ft_parse_match("*:[a-z0-9_]+", tl->info2 + 1))
				check_single_label(tl, tbf = file->head, 2, file);
			if (tl->info3 && ft_parse_match("*:[a-z0-9_]+", tl->info3 + 1))
				check_single_label(tl, tbf = file->head, 3, file);
			fill_intfo(tl);
			tl = tl->next;
		}
		taf = taf->next;
	}
	return (1);
}

int		check_param(int nb_tab, t_op op_tab[], char *info, int nb_param)
{
	char	byte;
	char	*reg;

	reg = ft_strnew(ft_strlen(LABEL_CHARS) + 3);
	ft_strcpy(reg, "[");
	reg[1] = LABEL_CHAR;
	ft_strcpy(reg + 2, LABEL_CHARS);
	ft_strcpy(reg + ft_strlen(LABEL_CHARS), "]+");
	byte = op_tab[nb_tab].params_types[nb_param];
	if (byte & T_REG)
	{
		if (ft_parse_match("r[0-9]+", info) && ft_atoi(info + 1) <= REG_NUMBER)
			return (1);
		else if (byte == T_REG)
			return (0);
	}
	if (byte & T_DIR)
	{
		if (info[0] == DIRECT_CHAR && (ft_parse_match("[0-9]+", info + 1) ||
					ft_parse_match(reg, info + 1)))
			return (1);
		else if (byte == T_DIR || byte == (T_DIR | T_REG))
			return (0);
	}
	if (ft_parse_match("[0-9]+", info[0] == '-' ? info + 1 : info))
		return (1);
	free(reg);
	return (0);
}

int		params_correspond(t_env *file)
{
	t_func	*func;
	t_line	*line;
	int		flag;

	flag = 0;
	func = file->head;
	while (func)
	{
		line = func->line;
		while (line)
		{
			if (!check_param(line->nb_tab, file->op_tab, line->info1, 0))
				flag = 1;
			if (line->info2 &&
					!check_param(line->nb_tab, file->op_tab, line->info2, 1))
				flag = 2;
			if (line->info3 &&
					!check_param(line->nb_tab, file->op_tab, line->info3, 2))
				flag = 3;
			if (flag != 0)
			{
				printf("Error line %d, param %d not valid\n", line->line_in_file,
						flag);
				exit(-1);
			}
			line = line->next;
		}
		func = func->next;
	}
	return (1);
}

int		get_method_pos(char *label_name, t_env *file)
{
	t_func	*func;
	t_line	*line;

	func = file->head;
	while (func && ft_strcmp(func->label, label_name))
		func = func->next;
	if (!func)
		asm_error("An unknown error occured");
	return (func->line->method_position);
}
