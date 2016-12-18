/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:42:48 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/18 21:29:41 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNPACK_H
# define UNPACK_H

# include "../../libft/includes/libft.h"
# include "../../op.h"

# define BYTE_START_CODE 2192

typedef struct s_type_a		t_type_a;
struct						s_type_a
{
	int						t_reg;
	int						t_dir;
	int						t_ind;
};

typedef struct s_type_func	t_type_func;
struct						s_type_func
{
	t_type_a				type[3];
	int						size;
	int						func;
	int						error;
};

typedef struct s_op			t_op;
struct						s_op
{
	char					*name;
	int						nb_param;
	char					params_types[4];
	int						opcode;
	int						nb_tours;
	char					*full_name;
	char					params_byte;
	char					index_size;
};

typedef struct s_file		t_file;
struct						s_file
{
	char					*name;
	char					*comment;
	int						size;
	char					*path;
	char					*content;
	int						fd;
	t_op					op[18];
};

void						read_function(t_file *cor, char *file);
void						op_tab(t_file *env);
void						unpack_error(char *str);
char						*get_content(int fd, char *result, char buf[1024]);
char						*get_x(t_file *cor, int from, int at);
int							todec(char *str);
char						*hex_to_bin_quad(char *str_1);
unsigned int				hex_to_dec(const char *str);
char						*read_name(char *file_player);
char						*read_comment(char *file_player);
void						read_magic(char *file_player);
void						read_op(char *op, t_file *cor, int *index);
void						unpack_error(char *str);
t_type_func					op_size_analys(char *op_size, int index,
							t_type_func list, int x);
t_type_func					check_jump(t_file *cor, char *op_size, int func);
int							special_func(int func);
char						*op_get_binary(int index, t_file *cor);
void						get_args(t_file *cor, t_type_func list, int index);
void						free_cor_file(t_file *cor_file);

#endif
