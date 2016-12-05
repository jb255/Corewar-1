/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:57:55 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/20 00:08:13 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

char	*ft_prepare_reg(void)
{
	char *reg;

	reg = ft_strnew(ft_strlen(LABEL_CHARS) + 4);
	reg[0] = LABEL_CHAR;
	ft_strcpy(reg + 1, "[");
	ft_strcpy(reg + 2, LABEL_CHARS);
	ft_strcpy(reg + ft_strlen(LABEL_CHARS) + 2, "]+");
	return (reg);
}

int		labels_are_defined(t_env *file)
{
	t_func	*taf;
	t_func	*tbf;
	t_line	*tl;
	char	*reg;

	taf = file->head;
	reg = ft_prepare_reg();
	while (taf != NULL)
	{
		tl = taf->line;
		while (tl != NULL)
		{
			if (tl->info1 && pm(reg, tl->info1 + (tl->info1[0] == '%' ? 1 : 0)))
				check_single_label(tl, tbf = file->head, 1, file);
			if (tl->info2 && pm(reg, tl->info2 + (tl->info2[0] == '%' ? 1 : 0)))
				check_single_label(tl, tbf = file->head, 2, file);
			if (tl->info3 && pm(reg, tl->info3 + (tl->info3[0] == '%' ? 1 : 0)))
				check_single_label(tl, tbf = file->head, 3, file);
			fill_intfo(tl);
			tl = tl->next;
		}
		taf = taf->next;
	}
	free(reg);
	return (1);
}

int		check_param(int nb_tab, t_op op_tab[], char *info, int nb_param)
{
	char	byte;
	char	*reg;
	char	res;

	reg = ft_prepare_reg();
	byte = op_tab[nb_tab].params_types[nb_param];
	res = 0;
	if (byte & T_REG)
	{
		if (pm("r[0-9]+", info) && ft_atoi(info + 1) <= REG_NUMBER)
			res = 1;
		else if (byte == T_REG)
			res = 0;
	}
	if (byte & T_DIR && !res)
	{
		if (info[0] == DIRECT_CHAR && (pm("[0-9]+", info[1] == '-' ? info + 2 :
			info + 1) || pm(reg, info + 1)))
			res = 1;
		else if (byte == T_DIR || byte == (T_DIR | T_REG))
			res = 0;
	}
	if (pm("[0-9]+", info[0] == '-' ? info + 1 : info) || pm(reg, info))
		res = 1;
	free(reg);
	return (res);
}

void	set_flag(t_line *line, int *flag, t_env *file)
{
	if (!check_param(line->nb_tab, file->op_tab, line->info1, 0))
		*flag = 1;
	if (line->info2 &&
			!check_param(line->nb_tab, file->op_tab, line->info2, 1))
		*flag = 2;
	if (line->info3 &&
			!check_param(line->nb_tab, file->op_tab, line->info3, 2))
		*flag = 3;
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
			set_flag(line, &flag, file);
			if (flag != 0)
			{
				ft_printf("Error line %d, param %d not valid\n",
						line->line_in_file, flag);
				exit(-1);
			}
			line = line->next;
		}
		func = func->next;
	}
	return (1);
}
