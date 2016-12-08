/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:42:48 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 20:14:39 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNPACK_H
# define UNPACK_H

# include "../../libft/includes/libft.h"
# include "../../op.h"

# define BYTE_START_CODE 2192


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

typedef struct s_file	t_file;
struct					s_file
{
	char		*name;
	char		*comment;
	int			size;
	char		*path;
	char		*content;
	int			fd;
};

void	unpack_error(char *str);
char			*get_content(int fd, char *result, char buf[1024]);
unsigned int    hex_to_dec(const char *str);
char			*read_name(char *file_player);
char			*read_comment(char *file_player);
void			read_magic(char *file_player);

#endif
