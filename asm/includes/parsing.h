/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:09:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/23 17:42:27 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "corewar.h"
# include "../../op.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_line		t_line;
struct						s_line
{
	char					*method;
	int						method_position;
	int						method_total;
	int						opcode;
	int						nb_tab;

	int						nb_info;
	char					*info1;
	int						intfo1[3];
	char					*info2;
	int						intfo2[3];
	char					*info3;
	int						intfo3[3];

	int						encod;
	int						line_in_file;
	struct s_line			*next;
};

typedef struct				s_op
{
	char					*name;
	int						nb_param;
	char					params_types[4];
	int						opcode;
	int						nb_tours;
	char					*full_name;
	char					params_byte;
	char					index_size;
}							t_op;

typedef struct s_func		t_func;
struct						s_func
{
	char					*label;
	int						line_in_file;
	t_line					*line;
	int						position;
	struct s_func			*next;
};

typedef struct s_env		t_env;
struct						s_env
{
	char					*name;
	char					*comment;
	char					*name_file;
	int						suite;
	int						y_line;
	t_func					*head;
	t_func					*tail;
	t_op					op_tab[17];

	int						method_position;
	int						method_total;
	int						nb_tab;
};

void						open_line(char *fichier, t_env *e);
void						fille_op_tab(t_env *env);
void						recup_label(char *str, t_env *e);
void						push_tail_label(t_func **begin_list,
	t_func **end_list, void *data, t_env *e);
char						**push_tail_method(t_line **begin_list,
	char **tab, int nb_arg, t_env *e);
int							pm(char *reg, char *str);
void						trim_args(t_env *env);
int							check_param(int nb_tab, t_op op_tab[],
	char *info, int nb_param);
int							params_correspond(t_env *file);
int							labels_are_defined(t_env *env);
int							get_method_pos(char *label_name, t_env *file);
int							get_byte_len(int nb_tab, char *arg, int n_inf);
unsigned char				*cut_nbr(unsigned nbr);
unsigned char				calc_octet(unsigned int *nbr,
	unsigned int diviseur);
void						check_single_label(t_line *line, t_func *func,
	int nb_inf, t_env *e);
void						name_comment(char *str, t_env *e);
int							epur_str(char *str);
int							coerence_str_optab(char *str, t_env *e);
void						create_file(t_env *e);
void						decoupage_nb(t_line *tmp);
char						*parsename(char *arg);
void						init_env(t_env *e);
int							verify_comma_continuity(char *str, int line);
void						fill_intfo(t_line *line);
t_line						*create_method(char **tab, int nb_arg, t_env *e);
char						*ft_prepare_reg(void);

#endif
