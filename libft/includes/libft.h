/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:33:49 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/20 04:42:32 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 15

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include <stdarg.h>
# include <dirent.h>
# include <grp.h>
# include <sys/stat.h>
# include <pwd.h>
# include <time.h>
# include <sys/types.h>
# include <sys/xattr.h>

# include "ft_printf.h"

typedef struct		s_list
{
	struct s_list	*next;
	void			*content;
	void			*data;
	size_t			content_size;
}					t_list;

void				ft_putstr(char const *s);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				ft_putendl(char const *s);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlen(const char *str);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				ft_counted(char *src);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*create_space(int c);
int					ft_strcmp (const char *s1, const char *s2);
int					ft_strncmp (const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_putchar(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_create_elem(void *data);
t_list				*ft_list_last(t_list *begin_list);
t_list				*ft_list_push_param(int ac, char **av);
t_list				*ft_list_find(t_list *begin_list,
					void *data_ref, int (*cmp)());
t_list				*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list				ft_list_reverse_fun(t_list *begin_list);
int					ft_list_size(t_list *begin_list);
void				ft_list_push_back(t_list **begin_list, void *data);
void				ft_list_push_front(t_list **begin_list, void *data);
void				ft_list_foreach_if(t_list *begin_list,
					void (*f)(void *), void *data_ref, int (*cmp)());
void				ft_list_foreach(t_list *begin_list, void (*f)(void *));
void				ft_list_reverse(t_list **begin_list);
void				ft_list_remove_if(t_list **begin_list,
					void *data_ref, int (*cmp)());
void				ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void				ft_list_sort(t_list **begin_list, int (*cmp)());
void				ft_sorted_list_insert(t_list **begin_list,
					void *data, int (*cmp)());
void				ft_sorted_list_merge(t_list **begin_list1,
					t_list *begin_list2, int (*cmp)());
void				ft_list_clear(t_list **begin_list);
void				ft_destroy(t_list *list);
void				ft_lstswap(void **str, void **str2);
int					ft_len(char const *s, char c);
int					ft_isegal(int c, int x);
int					ft_islower(int c, int x);
int					ft_word(char const *s, char c);
int					cmp(const char *cs, const char *ct);
int					get_next_line(int const fd, char **line);
char				*ft_str_reg_chr(const char *str, int c);
char				**ft_str_ext_split(char *str, char *ext);
int					ft_power(int nb, int pow);
void				ft_putstr_char(char c, int nb);
#endif
