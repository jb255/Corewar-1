/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 20:05:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 20:07:16 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

char	*get_content(int fd, char *result, char buf[1024])
{
	char	*tmp;
	int		i[2];

	tmp = NULL;
	i[0] = 0;
	i[1] = 0;
	while ((i[0] = read(fd, buf, 1023)) > 0)
	{
		tmp = result;
		result = malloc(i[1] + i[0] + 1);
		ft_memcpy(result, tmp, i[1]);
		ft_memcpy(result + i[1], buf, i[0]);
		i[1] += i[0];
		free(tmp);
	}
	return (result);
}

char	*read_name(char *file_player)
{
	char	*res = NULL;
	int		byte;
	int		index;

	byte = 4;
	res = malloc(PROG_NAME_LENGTH);
	index = 0;
	while (byte != PROG_NAME_LENGTH)
	{
		res[index] = file_player[byte];
		index++;
		byte++;
	}
	return (res);
}

char	*read_comment(char *file_player)
{
	char	*res = NULL;
	int		byte;
	int		index;

	byte = 140;
	res = malloc(COMMENT_LENGTH);
	index = 0;
	while (byte != COMMENT_LENGTH)
	{
		res[index] = file_player[byte];
		index++;
		byte++;
	}
	return (res);
}

void	read_magic(char *file_player)
{
	char	*magic[4];
	int		byte = 0;

	while (byte < 4)
	{
		magic[byte] = ft_sprintf("%x", file_player[byte]);
		byte++;
	}
	magic[byte] = ft_sprintf("%s%s%s", magic[1] + 6, magic[2] + 6, magic[3] + 6);
	if (!ft_strcmp(magic[0], "0") && !ft_strcmp(magic[byte], "ea83f3"))
		ft_printf("Magic correct\n");
	else
		unpack_error("Magic code incorrect");
	while (byte != -1)
	{
		free(magic[byte]);
		byte--;
	}
}
