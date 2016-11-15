/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 23:53:21 by jaustry           #+#    #+#             */
/*   Updated: 2016/11/15 22:16:47 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		coerence_str_optab(char *str, t_env *e) // verifie si le type 
{
	if ((str[0]) == 'r')
	{
		e->method_total += 1;
		return (1);
	}
	else if ((str[0]) == '%' && ((str[1] == ':') ||
		((ft_strlen(str) < 5) && str[1] != '0')))
	{
		e->method_total += 2;
		return (10);
	}
	else if ((str[0]) == '%')
	{
		e->method_total += 4;
		return (10);
	}
	else
	{
		e->method_total += 2;
		return (11);
	}
}

int			calculate_encod(char **tab, int nb_arg, t_env *e)
{
	int			encod;
	int			a;
	int			multiplicateur;
	int			binary_code;

	a = 1;
	multiplicateur = 128;
	while (a <= nb_arg)
	{
		binary_code = coerence_str_optab(tab[a], e);
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

void		argument_to_int(char *str, int *intfo)
{
	if ((str[0]) == 'r')
	{
		intfo[0] = T_REG;
		intfo[1] = ft_atoi(++str);
	}
	else if ((str[0]) == '%' && (str[1] == ':'))
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

t_line		*create_method(char **tab, int nb_arg, t_env *e)
{
	t_line		*list;

	if (!(list = (t_line *)ft_memalloc(sizeof(t_line))))
		return (NULL);
	list->method = tab[0];
	list->method_position = e->method_position + e->method_total;
	e->method_position += e->method_total;
	e->method_total = 0;
	list->encod = calculate_encod(tab, nb_arg, e);
	list->method_total = ++e->method_total;
	if (nb_arg >= 1)
	{
		list->info1 = tab[1];
		argument_to_int(tab[1], list->intfo1);
	}
	if (nb_arg >= 2)
	{
		list->info2 = tab[2];
		argument_to_int(tab[2], list->intfo2);
	}
	if (nb_arg >= 3)
	{
		list->info3 = tab[3];
		argument_to_int(tab[3], list->intfo3);
	}
	list->nb_info = nb_arg;
	list->opcode = e->op_tab[e->nb_tab].opcode;
	list->nb_tab = e->nb_tab;
	return (list);
}

void		push_tail_method(t_line **begin_list, char **tab, int nb_arg, t_env *e)
{
	t_line		*list;

	list = *begin_list;
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = create_method(tab, nb_arg, e);
	}
	else
	{
		*begin_list = create_method(tab, nb_arg, e);
	}
}

// Prend l'index de l'operation dans op_tab, l'argument ("r2", "%:khdfve"...) et le numero de
// l'information (donc 1, 2 ou 3) et renvoie le nombre d'octet a utiliser pour le codage
// de l'info en question
int			get_byte_len(int nb_tab, char *arg, int n_inf)
{
	int		tmp;

	tmp = ft_parse_match("r[0-9]+", arg);
	if (tmp)
		return (1);
	if (n_inf == 1)
	{
		if (nb_tab == 0 || nb_tab == 1 ||
			nb_tab == 5 || nb_tab == 6 ||
			nb_tab == 7 || nb_tab == 12)
			return (4);
		if (nb_tab == 2 || nb_tab == 8 ||
			nb_tab == 9 || nb_tab == 11 ||
			nb_tab == 13 || nb_tab == 14)
			return (2);
	}
	if (n_inf == 2)
	{
		if (nb_tab == 5 || nb_tab == 6 ||
			nb_tab == 7)
			return (4);
		if (nb_tab == 2 || nb_tab == 9 ||
			nb_tab == 10 || nb_tab == 13)
			return (2);
	}
	if (n_inf == 3)
	{
		if (nb_tab == 10)
			return (2);
	}
	return (0);
}
