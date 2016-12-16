/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 17:09:56 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 23:49:16 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		asm_error(char *str)
{
	ft_printf("%s\n", str);
	exit(-1);
}

void		syntax_error(t_env *e)
{
	ft_printf("Unknown syntax error line %d\n", e->y_line);
	exit(-1);
}
