/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 13:09:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 05:41:35 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../libft/includes/libft.h"
# include "parsing.h"
# include "../../op.h"

// typedef struct s_res_lst	t_res_lst;
// struct						s_res_lst
// {
// 	t_list					*dir;
// 	t_list					*file;
// 	t_list					*error;
// };

void		asm_error(char *str);

#endif
