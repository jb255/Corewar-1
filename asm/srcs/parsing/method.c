/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 23:53:21 by jaustry           #+#    #+#             */
/*   Updated: 2016/11/19 04:46:56 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			calculate_encod(char **tab, int nb_arg, t_env *e)
{
	int			encod;
	int			a;
	int			multiplicateur;
	int			binary_code;

	a = 1;
	multiplicateur = 128;
	encod = 0;
	while (a <= nb_arg)
	{
		binary_code = coerence_str_optab(tab[a], e);
		e->method_total += get_byte_len(e->nb_tab, tab[a], a);
		encod = encod + (binary_code / 10 * multiplicateur) +
		(binary_code % 10 * multiplicateur / 2);
		multiplicateur /= 4;
		a++;
	}
	if ((e->nb_tab) == 0 || (e->nb_tab) == 8 || (e->nb_tab) == 11 ||
		(e->nb_tab) == 16 || (e->nb_tab) == 17)
		return (0);
	e->method_total++;
	return (encod);
}

void		argument_to_int(char *str, int *intfo, int line)
{
	if ((str[0]) == 'r')
	{
		intfo[0] = T_REG;
		intfo[1] = ft_atoi(++str);
		if (intfo[1] > REG_NUMBER || intfo[1] < 0)
		{
			ft_printf("Register is not valid line %d : %s\n", line, str);
			exit(-1);
		}
	}
	else if ((str[0]) == '%' && (str[1] == LABEL_CHAR))
	{
		intfo[0] = T_DIR;
		intfo[1] = 0;
	}
	else if ((str[0]) == '%')
	{
		intfo[0] = T_DIR;
		intfo[1] = ft_atoi(++str);
	}
	else
	{
		intfo[0] = T_IND;
		intfo[1] = ft_atoi(str);
	}
}

void		set_infos(int nb_arg, t_line *list, char **tab)
{
	list->info1 = NULL;
	list->info2 = NULL;
	list->info3 = NULL;
	if (nb_arg >= 1)
	{
		list->info1 = ft_strdup(tab[1]);
		argument_to_int(tab[1], list->intfo1, list->line_in_file);
	}
	if (nb_arg >= 2)
	{
		list->info2 = ft_strdup(tab[2]);
		argument_to_int(tab[2], list->intfo2, list->line_in_file);
	}
	if (nb_arg >= 3)
	{
		list->info3 = ft_strdup(tab[3]);
		argument_to_int(tab[3], list->intfo3, list->line_in_file);
	}
}

t_line		*create_method(char **tab, int nb_arg, t_env *e)
{
	t_line		*list;

	if (!(list = (t_line *)ft_memalloc(sizeof(t_line))))
		return (NULL);
	list->method = ft_strdup(tab[0]);
	list->method_position = e->method_position + e->method_total;
	list->line_in_file = e->y_line;
	e->method_position += e->method_total;
	e->method_total = 0;
	list->encod = calculate_encod(tab, nb_arg, e);
	list->method_total = ++e->method_total;
	set_infos(nb_arg, list, tab);
	list->nb_info = nb_arg;
	list->opcode = e->op_tab[e->nb_tab].opcode;
	list->nb_tab = e->nb_tab;
	return (list);
}

int			get_byte_len(int nb_tab, char *arg, int n_inf)
{
	int		tmp;

	tmp = ft_parse_match("r[0-9]+", arg ? arg : "");
	if (n_inf == 1 && arg && !tmp)
	{
		if (arg[0] == '%' && (nb_tab == 0 || nb_tab == 1 || nb_tab == 5 ||
				nb_tab == 6 || nb_tab == 7 || nb_tab == 12))
			return (4);
		if (arg[0] != '%' || nb_tab == 2 || nb_tab == 8 || nb_tab == 9 ||
				nb_tab == 11 || nb_tab == 13 || nb_tab == 14)
			return (2);
	}
	if (n_inf == 2 && arg && !tmp)
	{
		if (nb_tab == 5 || nb_tab == 6 || nb_tab == 7)
			return (4);
		if (nb_tab == 2 || nb_tab == 9 ||
			nb_tab == 10 || nb_tab == 13)
			return (2);
	}
	if (n_inf == 3 && arg && !tmp)
		if (nb_tab == 10)
			return (2);
	return (tmp ? 1 : 0);
}
