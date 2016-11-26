/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 21:04:06 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 05:30:08 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include "color.h"

# define ABS(x) (x > 0 ? x : -x)
# define BUFFER 10

# define MAJOR(x)((x >> 24) & 0xff)
# define MINOR(x)(x & 0xffffff)

typedef struct s_result		t_result;
struct						s_result
{
	char					result[10];
	struct s_result			*next;
	struct s_result			*begin_list;
};

typedef struct s_info_str	t_info_str;
struct						s_info_str
{
	t_result				*data;
	char					arg;
	int						is_diez;
	int						str_size;
	int						flag_size;
	int						totalsize;
	int						size;
	int						buffer_count;
};

int							ft_printf(char const *format, ...);
char						*ft_sprintf(char const *format, ...);
int							data_next(t_info_str *list);
void						ft_select_printable(va_list ap, t_info_str *list,
							char c);
void						ft_checking_printf(char const *format,
							t_info_str *list, va_list ap);
int							ft_print_string(char *str, t_info_str *list);
void						ft_print_number(int nb, t_info_str *list);
void						ft_putclist(wchar_t c, t_info_str *list);
int							ft_printc(va_list ap);
char						ft_analyse(char const *str, t_info_str *list);
int							is_arg(char c);
int							intlen(int c);
void						ft_adress(void const *p, t_info_str *list);
char						*convert_char(wchar_t c);

#endif
