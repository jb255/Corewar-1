/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:44:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 20:50:55 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

void	unpack_error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}


t_type_func check_jump(t_file *cor, char *op_size, int func)
{
	int			index;
	int			x;
	t_type_func	list;

	index = 0;
	x = 0;
	ft_memset(&list, 0, sizeof(t_type_func));
	if (ft_strlen(op_size) != 8)
		unpack_error("wtf");
	list.size = 2;
	while (op_size[index] != '\0' && cor->op[func - 1].nb_param > x)
	{
		if (op_size[index] == '0' && op_size[index + 1] == '1')
		{
			list.type[x].t_reg++;
			list.size += 1;
		}
		else if (op_size[index] == '1' && op_size[index + 1] == '0')
		{
			list.type[x].t_dir++;
			if (func == 10 || func == 11 || func == 13)
				list.size += 2;
			else
				list.size += 4;
		}
		else if (op_size[index] == '1' && op_size[index + 1] == '1')
		{
			list.type[x].t_ind++;
			list.size += 2;
		}
		index += 2;
		x++;
	}
	return (list);
}

void	read_function(t_file cor, char *file)
{
	int		x;

	// ft_memset(&list, 0, sizeof(t_type_func));
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
