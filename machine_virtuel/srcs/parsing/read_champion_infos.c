/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champion_infos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 01:34:08 by vlancien          #+#    #+#             */
/*   Updated: 2016/10/22 01:34:30 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*read_name(char *file_player)
{
	char	*res = NULL;
	int		byte;
	int		index;

	byte = 4;
	res = malloc(PROG_NAME_LENGTH + 1);
	index = 0;
	while (index != PROG_NAME_LENGTH)
	{
		res[index] = file_player[byte];
		index++;
		byte++;
	}
	res[index] = 0;
	return (res);
}

char	*read_comment(char *file_player)
{
	char	*res = NULL;
	int		byte;
	int		index;

	byte = 140;
	res = malloc(COMMENT_LENGTH + 1);
	index = 0;
	while (index != COMMENT_LENGTH)
	{
		res[index] = file_player[byte];
		index++;
		byte++;
	}
	res[index] = 0;
	return (res);
}
