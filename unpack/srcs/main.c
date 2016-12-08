/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:44:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 20:42:34 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

void	unpack_error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

void	read_function(t_file cor, char *file)
{
	int		x;

	x = BYTE_START_CODE;
	while (x < cor.size)
	{
		ft_printf("%02x ", (unsigned char)(unsigned int)file[x]);
		x++;
	}
}

void	unpack(char *file)
{
	char		buf[1024];
	t_file		cor;

	ft_printf("Try to unpack: %s\n", file);
	if ((cor.fd = open(file, O_RDONLY)) < 0)
		unpack_error("Error file.");
	cor.content = get_content(cor.fd, NULL, buf);
	cor.size = lseek(cor.fd, 0, SEEK_END);
	cor.name = read_name(cor.content);
	cor.comment = read_comment(cor.content);
	read_magic(cor.content);
	read_function(cor, cor.content);
	ft_printf("name: %s\ncomment: %s\n", cor.name, cor.comment);
	close(cor.fd);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		unpack(av[1]);
	else
		unpack_error("Howto: ./unpack <file.cor>");
	return (0);
}
