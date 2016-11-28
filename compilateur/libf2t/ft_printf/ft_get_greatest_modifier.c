/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_greatest_modifier.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:52:53 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/07 09:58:50 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	second_part(char *fmt, int *i, T_LIST *trail)
{
	if (fmt[*i] == 'l' && fmt[*i + 1] != 'l' &&
			ft_strcmp(trail->mod, "ll"))
	{
		free(trail->mod);
		trail->mod = ft_strdup("l");
	}
	else if (fmt[*i] == 'h' && fmt[*i + 1] != 'h' &&
			trail->mod[0] != 'l')
	{
		free(trail->mod);
		trail->mod = ft_strdup("h");
	}
	else if (fmt[*i] == 'h' && fmt[*i + 1] == 'h' && trail->mod[0] == '-')
	{
		(*i)++;
		free(trail->mod);
		trail->mod = ft_strdup("hh");
	}
}

void		ft_get_greatest_modifier(char *fmt, int *i, T_LIST *trail)
{
	if (fmt[*i] == 'j' || trail->mod[0] == 'j')
	{
		free(trail->mod);
		trail->mod = ft_strdup("j");
	}
	else if (fmt[*i] == 'z' || trail->mod[0] == 'z')
	{
		free(trail->mod);
		trail->mod = ft_strdup("z");
	}
	else if (fmt[*i] == 'l' && fmt[*i + 1] == 'l')
	{
		(*i)++;
		free(trail->mod);
		trail->mod = ft_strdup("ll");
	}
	else
		second_part(fmt, i, trail);
}
