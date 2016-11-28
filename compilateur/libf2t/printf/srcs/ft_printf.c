/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 23:48:56 by vlancien          #+#    #+#             */
/*   Updated: 2016/09/27 21:10:43 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_clean_str(char const *format, t_info_str *list)
{
	intmax_t		index;
	char			c;

	index = list->size;
	if (list->size)
		index = data_next(list);
	while (*format != '%' && *format != '\0')
	{
		c = *format;
		list->data->result[index] = c;
		index++;
		format++;
		list->size = index;
		if (index == BUFFER)
		{
			write(1, list->data->result, index);
			index = data_next(list);
		}
		if (*format == '\0' || *format == '%')
			write(1, list->data->result, index);
	}
	return ((char*)format);
}

void		ft_checking_printf(char const *format, t_info_str *list, va_list ap)
{
	char		c;

	list->flag_size = 0;
	while (*format != '\0')
	{
		if (*format != '%' && *format != '\0')
			format = get_clean_str(format, list);
		if (*format == '%')
		{
			c = ft_analyse(format, list);
			format = format + list->flag_size;
			list->flag_size = 0;
			ft_select_printable(ap, list, c);
		}
		if (*format == '\0')
			break ;
	}
	return ;
}

int			ft_printf(char const *format, ...)
{
	va_list		ap;
	t_info_str	*list;

	list = (t_info_str*)ft_memalloc(sizeof(t_info_str));
	list->data = (t_result*)ft_memalloc(sizeof(t_result));
	va_start(ap, format);
	ft_checking_printf(&(*format), list, ap);
	va_end(ap);
	free(list->data);
	free(list);
	return (1);
}
