/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 20:05:50 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/18 19:13:51 by vlancien         ###   ########.fr       */
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
	if (i[0] == -1)
		unpack_error("Unable to read file");
	return (result);
}

char	*read_name(char *file_player)
{
	char	*res;
	int		byte;
	int		index;

	res = NULL;
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
	char	*res;
	int		byte;
	int		index;

	res = NULL;
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
	int		byte;

	byte = 0;
	while (byte < 4)
	{
		magic[byte] = ft_sprintf("%x", file_player[byte]);
		byte++;
	}
	magic[byte] = ft_sprintf("%s%s%s", magic[1] + 6, magic[2] + 6,
		magic[3] + 6);
	if (ft_strcmp(magic[0], "0") || ft_strcmp(magic[byte], "ea83f3"))
		unpack_error("Fichier incorrect. [ Magic error ]");
	while (byte != -1)
	{
		free(magic[byte]);
		byte--;
	}
}

void	free_cor_file(t_file *cor_file)
{
	free(cor_file->content);
	free(cor_file->name);
	free(cor_file->comment);
	free(cor_file);
}
