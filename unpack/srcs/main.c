/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:44:05 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/12 14:06:56 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

void			unpack_error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

t_type_func		check_jump(t_file *cor, char *op_size, int func)
{
	int			index;
	int			x;
	t_type_func	list;

	index = 0;
	x = 0;
	ft_memset(&list, 0, sizeof(t_type_func));
	if (ft_strlen(op_size) != 8)
		unpack_error("wtf ??");
	list.size = 2;
	while (op_size[index] != '\0' && cor->op[func].nb_param > x)
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
	list.func = func;
	free(op_size);
	return (list);
}

int				special_func(int func)
{
	if (func == 12 || func == 15)
		return (3);
	else if (func == 1)
		return (5);
	else if (func == 9 || func == 16)
		return (3);
	ft_printf("Can't find size for %d\n", func);
	exit(1);
	return (0);
}

char			*op_get_binary(int index, t_file *cor)
{
	char	*binary;

	binary = NULL;
	binary = ft_sprintf("%08b", (unsigned char)(cor->content[index + 1]));
	return (binary);
}

void			print_args(t_type_a arg, int *index, int func, t_file *cor)
{
	if (arg.t_reg)
	{
		ft_printf("r%d", todec(get_x(cor, *index + 2, *index + 3)));
		*index += 1;
	}
	if (arg.t_ind)
	{
		ft_printf("%d", todec(get_x(cor, *index + 2, *index + 4)));
		*index += 2;
	}
	if (arg.t_dir)
	{
		if (func == 10 || func == 11 || func == 13)
		{
			ft_printf("%%%d", todec(get_x(cor, *index + 2, *index + 4)));
			*index += 2;
		}
		else
		{
			ft_printf("%%%d", todec(get_x(cor, *index + 2, *index + 6)));
			*index += 4;
		}
	}
}
void			get_args(t_file *cor, t_type_func list, int index)
{
	print_args(list.type[0], &index, list.func, cor);
	if (list.type[1].t_reg || list.type[1].t_ind || list.type[1].t_dir)
	{
		ft_printf(", ");
		print_args(list.type[1], &index, list.func, cor);
	}
	if (list.type[2].t_reg || list.type[2].t_ind || list.type[2].t_dir)
	{
		ft_printf(", ");
		print_args(list.type[2], &index, list.func, cor);
	}
	ft_printf("\n");
}

void			read_op(char *op, t_file *cor, int *index)
{
	t_type_func		list;
	int				func;

	list = check_jump(cor, op_get_binary(*index, cor), hex_to_dec(op));
	func = list.func;
	if (func > 0 && func < 17 && func != 1 && func != 9 && func != 12
		&& func != 15)
	{
		ft_printf("%s\t", cor->op[func].name);
		get_args(cor, list, *index);
	}
	else
	{
		list.size = special_func(func);
		ft_printf("%s\t%%%d\n", cor->op[func].name, todec(get_x(cor, *index + 1,
			*index + list.size)));
	}
	(*index) += list.size;
	free(op);
}

void			read_function(t_file *cor, char *file)
{
	int		x;

	x = BYTE_START_CODE;
	while (x < cor->size)
		read_op(ft_sprintf("%02x", (short int)file[x]), cor, &x);
}

// struct						s_file
// {
// 	char					*name;
// 	char					*comment;
// 	int						size;
// 	char					*path;
// 	char					*content;
// 	int						fd;
// 	t_op					op[18];
// };

void			free_cor_file(t_file *cor_file)
{
	free(cor_file->content);
	free(cor_file->name);
	free(cor_file->comment);
	free(cor_file);
}

void			unpack(char *file)
{
	char		buf[1024];
	t_file		*cor_file;

	cor_file = (t_file *)ft_memalloc(sizeof(t_file));
	op_tab(cor_file);
	if ((cor_file->fd = open(file, O_RDONLY)) < 0)
		printf("fd %d\n", cor_file->fd);
	cor_file->content = get_content(cor_file->fd, NULL, buf);
	cor_file->size = lseek(cor_file->fd, 0, SEEK_END);
	cor_file->name = read_name(cor_file->content);
	cor_file->comment = read_comment(cor_file->content);
	ft_printf(".name \"%s\"\n", cor_file->name);
	ft_printf(".comment \"%s\"\n\n", cor_file->comment);
	read_magic(cor_file->content);
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
