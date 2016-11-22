/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:11:09 by mlevieux          #+#    #+#             */
/*   Updated: 2016/05/06 11:43:14 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFTPRINTF_H
# define _LIBFTPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

# include "libft.h"

# define INT_TYPE 'd'
# define CHAR_TYPE 'c'
# define POINTER_TYPE 'p'
# define STRING_TYPE 's'
# define WSTRING_TYPE 'S'
# define DOUBLE_TYPE 'f'
# define ERRNO 'm'
# define PERCENT '%'
# define T_LIST t_list_printf

typedef struct	s_list_printf
{
	int						start_index;
	int						end_index;
	int						minus;
	int						plus;
	int						alternate;
	int						z_pad;
	int						space;
	int						width;
	int						accuracy;
	char					*mod;
	char					format;
	char					type;
	int						incomplete;
	int						is_signed;
	int						oct_num;
	int						unused;
	char					*w_size;
	struct s_list_printf	*next;
}				t_list_printf;

char			*ft_base(intmax_t num, int base);
char			*ft_ubase(uintmax_t num, int base);
char			*ft_repstr(char *str, int start, int end, char *to_insert);
char			*ft_strset(char *str, int len, char c);
char			*ft_set_width(char *result, T_LIST *trail);
char			*ft_set_length(T_LIST *trail, char *result);
char			*ft_alternate(char *result, T_LIST *trail);
char			*ft_apply_flag(char *result, T_LIST *trail);
int				ft_int_type(T_LIST *args_data, va_list *args, char **result);
int				ft_call_int(intmax_t number, T_LIST *trail, char **print);
int				ft_call_uint(uintmax_t number, T_LIST *trail, char **print);
int				ft_char_type(T_LIST *args_data, va_list *args, char **result);
int				ft_call_char(wchar_t wc, T_LIST *trail, char **print);
int				ft_double_type(T_LIST *args_data, va_list *args,
					char **result);
char			*ft_conv_float(long double to_print, int accuracy);
char			*ft_conv_exp(long double number, T_LIST *trail);
int				ft_call_float(long double number, T_LIST *trail, char **print);
int				ft_call_pointer(unsigned long p, T_LIST *trail, char **print);
wchar_t			*ft_conv_wchar(char *str);
unsigned char	*ft_transfer_wchar(wchar_t c, int *oct_num);
char			*ft_transfer_wchars(wchar_t *wstr, T_LIST *trail,
					unsigned char **p);
int				ft_call_wstring(wchar_t *wstring, T_LIST *trail, char **print,
					int code);
void			ft_move_index(T_LIST **trail, int padding);
int				ft_call_errno(T_LIST *trail, char **print);
int				ft_call_percent(T_LIST *trail, char **print);
int				ft_call_wildcard(T_LIST *trail, char **print);
int				ft_type_crossroad(T_LIST *args_data, va_list *args,
					char **result);
void			ft_free_list(T_LIST **start);
int				ft_is_format(char format);
int				ft_is_valid(char c);
int				ft_check_fmt(char const *fmt);
T_LIST			*ft_make_node(void);
int				ft_is_modifier(char *str);
void			ft_get_greatest_modifier(char *fmt, int *counter,
					T_LIST *trail);
void			ft_get_width(char *location, int *counter, T_LIST *trail);
void			ft_get_accuracy(char *location, int *counter, T_LIST *trail);
T_LIST			*ft_get_args(char *fmt);
int				ft_printf(char const *fmt, ...);
void			ft_round(long double *num, int accuracy);
void			ft_get_fmt(T_LIST *trail, char fmt);
void			ft_strtoupper(char *str);

#endif
