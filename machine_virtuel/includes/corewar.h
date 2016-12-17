/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:09:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/16 18:02:52 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../libft/includes/libft.h"
# include "../../op.h"
# include <fcntl.h>
# include <sys/types.h>
# include <display.h>
# include "function.h"
# include "players.h"

# define TRUE 1
# define FALSE 0

unsigned char tab[MEM_SIZE];
int tab2[MEM_SIZE];

# define BYTE_START_CODE 2192
# define MAX_PROCESS 100000

typedef struct s_flag	t_flag;
struct					s_flag
{
	int					flag_n;
	int					pause;
	int					obo;
	int					flag_dump;
	int					dump;
	int					flag_number;
	int					is_decremented;
};

typedef struct s_arena	t_arena;
struct					s_arena
{
	int					cycle;
	int					cycle_to_die;
	int					live_call;
	int					time_cycle;
	int					cycle_total;
	int					winner;
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

typedef struct s_env	t_env;
struct					s_env
{
	t_flag				flag;
	t_player			players[MAX_PLAYERS];
	int					active_players;
	int					active_process;
	int					memory_data[4];
	t_arena				arena;
	t_window			window;
	t_process			process[MAX_PROCESS + 10000];
	int					fd;
	t_op				op[17];
};

int		to_int_getx(char *str);
void	display_info_menu(t_env *e);
void			vm_error(char *str);
void			parsing_arg(char **arg, t_env *e);
void			reading_file(t_env *e, int x);
void			read_instruction(t_env *e, int x);
void			op_tab(t_env *e);
int				instruct_tab_value(char *str);
int				get_func_method(int jump, char **action_, char *tmp);

//Players
char			*read_comment(char *file_player);
char			*read_name(char *file_player);

char			*hex_to_bin_quad(char *str_1);
unsigned int    hex_to_dec(const char *str);

void			put_player(t_env *e);
void			player_to_tab(t_env *e, int x);
//Players

// void		new_emptyprocess(t_process **begin_list, t_env *e);
// void		init_temp_process(t_env *e);
int				jump(int code, char *status);
int				key_hook(t_env *e);
char			*to_opcode(char c, char c1);
void			init_process(t_env *e, int nb);
void			set_process(t_env *e, int process_nb, int x, int creator);
int				get_first_ld(t_env *e, t_type_func list, int *error, int xproc);
// function
void		live_func(t_env *e, int xproc, t_type_func list);
void		ld_func(t_env *e, int xproc, t_type_func list);
void		st_func(t_env *e, int xproc, t_type_func list);
void		add_func(t_env *e, int xproc, t_type_func list);
void		sub_func(t_env *e, int xproc, t_type_func list);
void		and_func(t_env *e, int xproc, t_type_func list);
void		or_func(t_env *e, int xproc, t_type_func list);
void		xor_func(t_env *e, int xproc, t_type_func list);
void		zjump_func(t_env *e, int xproc, t_type_func list);
void		ldi_func(t_env *e, int xproc, t_type_func list);
void		sti_func(t_env *e, int xproc, t_type_func list);
void		fork_func(t_env *e, int xproc, t_type_func list);
void		lld_func(t_env *e, int xproc, t_type_func list);
void		lldi_func(t_env *e, int xproc, t_type_func list);
void		lfork_func(t_env *e, int xproc, t_type_func list);
void		aff_func(t_env *e, int xproc, t_type_func list);

void	update_cycle(t_env *e);
int				check_all_processlive(t_env *e);
void			victory_player(t_env *e);
t_type_func 	check_jump(t_env *e, char *op_size, int func);
t_type_func		find_label(t_env *e, int x);
//

void	victory_player(t_env *e);
void	update_cycle(t_env *e);
void	check_all_process(t_env *e);
void	press_start(t_env *e);

// WorkFunc
char	*get_x_from_position(t_env *e, int from, int at);
int		octet_precision(char *hex, int octet);
void	write_from_x(t_env *e, int from, int data, int octet);
int		is_register_valid(t_env *e, int xproc, int position);
void	write_from_tab2(int position, int size, int id);
int		name_process(t_env *e, char	*name);
int		get_xorandor_arg(t_type_a list, t_env *e, int xproc, int *place);
int		reg_funcheck_and(t_env *e, int xproc, int place);
int		get_i0_func_and(t_type_func list, t_env *e, int xproc, int *place);
int		get_i1_func_and(t_type_func list, t_env *e, int xproc, int *place);
int		get_i02_func_and(t_type_func list, t_env *e, int xproc, int *place);
int		get_i1_2_func_and(t_type_func list, t_env *e, int xproc, int *place);
void	write_tab(void);
void	delete_process(t_env *e, int process_nb);
//
#endif
