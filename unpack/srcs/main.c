/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:44:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/18 21:36:28 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

void			unpack_error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

char			*op_get_binary(int index, t_file *cor)
{
	char	*binary;

	binary = NULL;
	binary = ft_sprintf("%08b", (unsigned char)(cor->content[index + 1]));
	return (binary);
}

void			read_function(t_file *cor, char *file)
{
	int		x;

	x = BYTE_START_CODE;
	while (x < cor->size)
		read_op(ft_sprintf("%02x", (short int)file[x]), cor, &x);
}

void			unpack(char *file)
{
	char		buf[1024];
	t_file		*cor_file;

	cor_file = (t_file *)ft_memalloc(sizeof(t_file));
	op_tab(cor_file);
	if ((cor_file->fd = open(file, O_RDONLY)) < 0)
		unpack_error("Error file");
	cor_file->content = get_content(cor_file->fd, NULL, buf);
	cor_file->size = lseek(cor_file->fd, 0, SEEK_END);
	cor_file->name = read_name(cor_file->content);
	cor_file->comment = read_comment(cor_file->content);
	read_magic(cor_file->content);
	ft_printf(".name \"%s\"\n", cor_file->name);
	ft_printf(".comment \"%s\"\n\n", cor_file->comment);
	read_function(cor_file, cor_file->content);
	close(cor_file->fd);
	free_cor_file(cor_file);
}

int				main(int ac, char **av)
{
	if (ac == 2)
		unpack(av[1]);
	else
		unpack_error("Howto: ./unpack <file.cor>");
	return (0);
}
