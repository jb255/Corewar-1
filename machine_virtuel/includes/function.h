/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:08:57 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/28 10:35:43 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

typedef unsigned char	t_u8;
typedef unsigned short	t_u16;
typedef unsigned int	t_u32;

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


#endif
