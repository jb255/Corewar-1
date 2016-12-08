/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hextodec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 20:06:22 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 20:06:48 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

unsigned int    hex_to_dec(const char *str)
{
    unsigned int total;
    int i;

    total = 0;
    i = 0;
    while (0 < str[i] && str[i] < 33)
        i++;
    while ((str[i] >= '0' && str[i] <= '9') ||
            (str[i] >= 'A' && str[i] <= 'F') ||
            (str[i] >= 'a' && str[i] <= 'f'))
    {
        if (str[i] >= '0' && str[i] <= '9')
            total = (total * 16) + (str[i++] - '0');
        if (str[i] >= 'A' && str[i] <= 'F')
            total = (total * 16) + (str[i++] - 'A' + 10);
        if (str[i] >= 'a' && str[i] <= 'f')
            total = (total * 16) + (str[i++] - 'a' + 10);
    }
    return (total);
}
