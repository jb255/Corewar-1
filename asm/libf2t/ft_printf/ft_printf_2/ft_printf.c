/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 15:34:27 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 11:35:03 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	printf_loop(T_LIST **tmp, va_list *args, char **result)
{
	int state_value;

	state_value = 1;
	while (--((*tmp)->unused))
		va_arg(*args, void*);
	if ((*tmp)->width == -10)
		(*tmp)->width = va_arg(*args, int);
	if ((*tmp)->accuracy == -10)
		(*tmp)->accuracy = va_arg(*args, int);
	if (ft_type_crossroad(*tmp, args, result) == 0)
		state_value = 0;
	free((*tmp)->mod);
	*tmp = (*tmp)->next;
	return (state_value);
}

static void	ft_print(char *str)
{
	int		i;
	char	z;

	i = 0;
	z = ft_strlen(str);
	while (str[i] != 0)
	{
		if (str[i] == -1)
			str[i] = 0;
		i++;
	}
	write(1, str, z);
}

int			ft_printf(char const *fmt, ...)
{
	va_list		args;
	int			state_value;
	T_LIST		**list;
	char		*result;

	list = (T_LIST**)malloc(sizeof(T_LIST*) * 2);
	va_start(args, fmt);
	result = ft_strdup(fmt);
	state_value = 1;
	list[0] = ft_get_args(ft_strdup(fmt));
	list[1] = list[0];
	while (list[1])
		state_value = printf_loop(list + 1, &args, &result);
	state_value = (state_value) ? ft_strlen(result) : -1;
	ft_print(result);
	free(result);
	ft_free_list(list);
	free(list);
	return (state_value);
}
