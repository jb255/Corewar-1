/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:44:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/08 21:47:24 by vlancien         ###   ########.fr       */
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
	(void)cor;
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

int				special_func(int func)
{
	if (func == 12 || func == 15)
		return (3);
	else if (func == -1)
		return (1);
	else if (func == 1)
		return (5);
	else if (func == 9 || func == 16)
		return (3);
	return (0);
}

char	*op_get_binary(int index, t_file *cor)
{
	char	*tmp;
	char	*binary;

	binary = NULL;
	tmp = NULL;
	tmp = ft_sprintf("%02x", (unsigned char)(unsigned int)cor->content[index + 1]);
	binary = hex_to_bin_quad(tmp);
	free(tmp);
	return (binary);
}

void 	single_arg(int *curr, t_type_a list, int index, t_file *cor)
{
	int		nb;
	char	res[25];

	nb = 0;
	(void)res;
	(void)nb;
	(void)curr;
	if (list.t_reg)
	{
		printf("r%x\n", (unsigned char)(unsigned int)cor->content[index + 1]);
	}
}

void	get_args(t_file *cor, t_type_func list, int index, int code)
{
	int		curr_pos;

	curr_pos = 2;
	if (code == 1)
	{
		single_arg(&curr_pos, list.type[0], index, cor);
		// single_arg(&curr_pos, list.type[1], index, cor);
		// single_arg(&curr_pos, list.type[2], index, cor);
	}
	// else
	// {
	// 	break;
	// }
}

void	read_op(char *op, t_file *cor, int *index)
{
	t_type_func		list;
	int				func;

	list = check_jump(cor, op_get_binary(*index, cor), hex_to_dec(op));
	func = ft_atoi(op) - 1;
	if (func > 0 && func < 17 && func != 0 && func != 8 && func != 11 && func != 14 && func != 15)
	{
		printf("Function: %s\n",cor->op[func].name);
		printf("Octet de codage: %s\n", ft_sprintf("%02x", (unsigned char)(unsigned int)cor->content[*index + 1]));
		printf("Argument 1: reg.%d ind.%d dir.%d\n", list.type[0].t_reg, list.type[0].t_ind, list.type[0].t_dir);
		printf("Argument 2: reg.%d ind.%d dir.%d\n", list.type[1].t_reg, list.type[1].t_ind, list.type[1].t_dir);
		printf("Argument 3: reg.%d ind.%d dir.%d\n", list.type[2].t_reg, list.type[2].t_ind, list.type[2].t_dir);
		get_args(cor, list, *index, 1);
	}
	else
	{
		list.size = special_func(func + 1);
		get_args(cor, list, *index, 0);
	}
	(*index) += list.size;
	free(op);
}

void	read_function(t_file *cor, char *file)
{
	int		x;
	char	*tmp;

	tmp = NULL;
	// ft_memset(&list, 0, sizeof(t_type_func));
	x = BYTE_START_CODE;
	while (x < cor->size)
	{
		read_op(ft_sprintf("%02x", (unsigned char)(unsigned int)file[x]), cor, &x);
		free(tmp);
	}
}

void	unpack(char *file)
{
	char		buf[1024];
	t_file		*cor_file;

	cor_file = (t_file *)ft_memalloc(sizeof(t_file));
	op_tab(cor_file);
	ft_printf("Try to unpack: %s\n", file);
	if ((cor_file->fd = open(file, O_RDONLY)) < 0)
		printf("fd %d\n", cor_file->fd);
		// unpack_error("Error file.");
	cor_file->content = get_content(cor_file->fd, NULL, buf);
	cor_file->size = lseek(cor_file->fd, 0, SEEK_END);
	cor_file->name = read_name(cor_file->content);
	cor_file->comment = read_comment(cor_file->content);
	read_magic(cor_file->content);
	read_function(cor_file, cor_file->content);
	ft_printf("name: %s\ncomment: %s\n", cor_file->name, cor_file->comment);
	close(cor_file->fd);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		unpack(av[1]);
	else
		unpack_error("Howto: ./unpack <file.cor>");
	return (0);
}
