/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 04:41:34 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/19 04:42:09 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			coerence_str_optab(char *str, t_env *e)
{
	if ((str[0]) == 'r')
		return (1);
	else if ((str[0]) == '%' && ((str[1] == ':') ||
		((ft_strlen(str) < 5) && str[1] != '0' && str[1] != '1')))
		return (10);
	else if ((str[0]) == '%')
		return (10);
	else
		return (11);
	e->nb_tab = e->nb_tab;
}

char		**push_tail_method(t_line **begin, char **tab, int nb_arg, t_env *e)
{
	t_line		*list;

	list = *begin;
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = create_method(tab, nb_arg, e);
	}
	else
		*begin = create_method(tab, nb_arg, e);
	return (tab);
}

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
