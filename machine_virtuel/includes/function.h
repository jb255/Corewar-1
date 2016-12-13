/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 22:08:57 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 20:43:53 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

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
