/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:41:35 by jaustry           #+#    #+#             */
/*   Updated: 2016/12/07 15:41:37 by jaustry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

unsigned int	little_to_big(unsigned int little)
{
	unsigned int	big;

	big = ((little >> 24) & 0xff) | ((little << 8) & 0xff0000) |
	((little >> 8) & 0xff00) | ((little << 24) & 0xff000000);
	return (big);
}