/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 09:19:46 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/28 09:24:57 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	ft_print_fd(char *str, int fd)
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
	write(fd, str, z);
}

int			ft_printf_fd(int fd, char const *fmt, ...)
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
	ft_print_fd(result, fd);
	free(result);
	ft_free_list(list);
	free(list);
	return (state_value);
}
