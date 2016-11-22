/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:52:34 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/05 16:46:41 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void		if_forest(char *fmt, int i, T_LIST *tmp)
{
	if (fmt[i] == '-')
		tmp->minus = 1;
	else if (fmt[i] == '+')
		tmp->plus = 1;
	else if (fmt[i] == '0')
		tmp->z_pad = 1;
	else if (fmt[i] == '#')
		tmp->alternate = 1;
	else if (fmt[i] == ' ')
		tmp->space = 1;
	else if (fmt[i] == '*' && tmp->width != -10)
		tmp->width = -10;
	else if (fmt[i] == '*' && tmp->width != 0 && tmp->accuracy == -1)
		tmp->accuracy = -10;
}

static void		intern_loop(int *i, char *fmt, T_LIST *tmp)
{
	if (fmt[*i] == '-' || fmt[*i] == '+' || fmt[*i] == '0' || fmt[*i] == '#' ||
		fmt[*i] == ' ' || (fmt[*i] == '*' && ((tmp->width != -10) ||
			(tmp->width != 0 && tmp->accuracy == -1))))
		if_forest(fmt, *i, tmp);
	else if (ft_isdigit(fmt[*i]))
	{
		tmp->unused = (tmp->width == -10) ? tmp->unused + 1 : tmp->unused;
		ft_get_width(fmt, i, tmp);
	}
	else if (fmt[*i] == '.')
		ft_get_accuracy(fmt, i, tmp);
	else if (ft_is_modifier(&(fmt[*i])))
		ft_get_greatest_modifier(fmt, i, tmp);
	else if (fmt[*i] == '*')
		tmp->unused++;
	(*i)++;
}

static void		intern_condition(int *i, T_LIST **tmp, char *fmt)
{
	(*tmp)->next = ft_make_node();
	*tmp = (*tmp)->next;
	(*tmp)->start_index = (*i)++;
	while (ft_is_valid(fmt[*i]) && !ft_is_format(fmt[*i]))
		intern_loop(i, fmt, (*tmp));
	if (ft_is_format(fmt[*i]))
		ft_get_fmt((*tmp), fmt[*i]);
	else
	{
		(*tmp)->incomplete = 1;
		if (fmt[*i])
			(*tmp)->format = fmt[*i];
	}
	(*tmp)->end_index = ((*tmp)->format) ? *i : *i - 1;
}

T_LIST			*ft_get_args(char *fmt)
{
	T_LIST	*args;
	T_LIST	*tmp;
	int		i;

	args = ft_make_node();
	tmp = args;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			intern_condition(&i, &tmp, fmt);
		}
		i++;
	}
	free(fmt);
	tmp = args->next;
	free(args->mod);
	free(args);
	return (tmp);
}
