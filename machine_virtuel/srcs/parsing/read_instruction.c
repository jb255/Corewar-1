/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 09:02:53 by viko              #+#    #+#             */
/*   Updated: 2016/12/13 19:15:12 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		instruct_tab_value(char *str)
{
	int		value;

	value = hex_to_dec(str);
	if (value > 0 && value < 17)
		return (value);
	return (-1);
}
