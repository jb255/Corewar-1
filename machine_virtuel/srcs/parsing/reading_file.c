/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 18:07:34 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/13 19:15:35 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

char	*print_hexa(unsigned char c, int byte)
{
	unsigned char	val1;
	unsigned char	val2;
	char			*str;

	str = ft_memalloc(sizeof(char) * 2 + 1);
	if (!str)
		vm_error("Error malloc");
	val1 = c / 16;
	val2 = c % 16;
	if (val1 > 9)
		val1 += -10 + 'a';
	else
		val1 += '0';
	if (val2 > 9)
		val2 += -10 + 'a';
	else
		val2 += '0';
	str[0] = val1;
	str[1] = val2;
	if (byte == 0)
		str[1] = 'x';
	return (str);
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
	while (byte != -1)
	{
		free(magic[byte]);
		byte--;
	}
}

void	reading_file(t_env *e, int x)
{
	int		fd;
	char	buf[1024];

	if ((fd = open(e->players[x].path, O_RDONLY)) < 0){
		printf("%s\n", e->players[x].path);
		vm_error("Error file.");
	}
	e->players[x].file = get_content(fd, NULL, buf);
	e->players[x].size = lseek(fd, 0, SEEK_END);
	close(fd);
	e->players[x].name = read_name(e->players[x].file);
	e->players[x].comment = read_comment(e->players[x].file);
	read_magic(e->players[x].file);
}
