/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:15:51 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 01:45:10 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"

void	display_init_color(void)
{
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(20, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(30, COLOR_BLUE, COLOR_YELLOW);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(40, COLOR_BLACK, COLOR_RED);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
}
