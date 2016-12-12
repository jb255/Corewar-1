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
	// ft_printf("Check jump_ Func[%d] // Opsize[%s]\n", func, op_size);
	ft_memset(&list, 0, sizeof(t_type_func));
	if (ft_strlen(op_size) != 8)
		unpack_error("wtf");
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
	// ft_printf("Size trouve = %d\n", list.size);
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
	unpack_error("x");
	return (0);
}

char	*op_get_binary(int index, t_file *cor)
{
	char	*binary;

	binary = NULL;
	binary = ft_sprintf("%08b", (unsigned char)(cor->content[index + 1]));
	return (binary);
}

void	get_args(t_file *cor, t_type_func list, int index)
{
	if (list.type[0].t_reg)
	{
		ft_printf("r%d", todec(get_x(cor, index + 2, index + 3)));
		index += 1;
		// ft_printf("\n");

	}
	if (list.type[0].t_ind)
	{
		ft_printf("%d", todec(get_x(cor, index + 2, index + 4)));
		index += 2;
		// ft_printf("\n");

	}
	if (list.type[0].t_dir)
	{
		if (list.func == 10 || list.func == 11 || list.func == 13)
		{
			ft_printf("%%%d", todec(get_x(cor, index + 2, index + 4)));
			index += 2;
		}
		else{
			ft_printf("%%%d", todec(get_x(cor, index + 2, index + 6)));
			index += 4;
		}
		// ft_printf("\n");

	}
	if (list.type[1].t_reg)
	{
		ft_printf(", r%d", todec(get_x(cor, index + 2, index + 3)));
		index += 1;
		// ft_printf("\n");

	}
	if (list.type[1].t_ind)
	{
		ft_printf(", %d", todec(get_x(cor, index + 2, index + 4)));
		index += 2;
		// ft_printf("\n");

	}
	if (list.type[1].t_dir)
	{
		if (list.func == 10 || list.func == 11 || list.func == 13)
		{
			ft_printf(", %%%d", todec(get_x(cor, index + 2, index + 4)));
			index += 2;
		}
		else{
			ft_printf(", %%%d", todec(get_x(cor, index + 2, index + 6)));
			index += 4;
		}
		// ft_printf("\n");

	}
	if (list.type[2].t_reg)
	{
		ft_printf(", r%d", todec(get_x(cor, index + 2, index + 3)));
		index += 1;
		// ft_printf("\n");

	}
	if (list.type[2].t_ind)
	{
		ft_printf(", %d", todec(get_x(cor, index + 2, index + 4)));
		index += 2;
		// ft_printf("\n");

	}
	if (list.type[2].t_dir)
	{
		if (list.func == 10 || list.func == 11 || list.func == 13)
		{
			ft_printf(", %%%d", todec(get_x(cor, index + 2, index + 4)));
			index += 2;
		}
		else{
			ft_printf(", %%%d", todec(get_x(cor, index + 2, index + 6)));
			index += 4;
		}
		// ft_printf("\n");

	}
	ft_printf("\n");
}

void	read_op(char *op, t_file *cor, int *index)
{
	t_type_func		list;
	int				func;

	list = check_jump(cor, op_get_binary(*index, cor), hex_to_dec(op));
	func = list.func;
	if (func > 0 && func < 17 && func != 1 && func != 9 && func != 12 && func != 15)
	{
		// printf("Octet de codage: %s\n", ft_sprintf("%d", abs(cor->content[*index + 1])));
		// printf("Argument 1: reg.%d ind.%d dir.%d\n", list.type[0].t_reg, list.type[0].t_ind, list.type[0].t_dir);
		// printf("Argument 2: reg.%d ind.%d dir.%d\n", list.type[1].t_reg, list.type[1].t_ind, list.type[1].t_dir);
		// printf("Argument 3: reg.%d ind.%d dir.%d\n", list.type[2].t_reg, list.type[2].t_ind, list.type[2].t_dir);
		// ft_printf("%s\n",cor->op[func].name);
		ft_printf("%s\t",cor->op[func].name);
		get_args(cor, list, *index);
	}
	else
	{
		list.size = special_func(func);
		ft_printf("%s\t%%%d\n", cor->op[func].name, todec(get_x(cor, *index + 1, *index + list.size)));
	}
	(*index) += list.size;
	free(op);
}

void	read_function(t_file *cor, char *file)
{
	int		x;

	x = BYTE_START_CODE;
	while (x < cor->size)
	{
		read_op(ft_sprintf("%02x", (short int)file[x]), cor, &x);
	}
}

void	unpack(char *file)
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
	ft_printf(".name \"%s\"\n.comment \"%s\"\n\n", cor_file->name, cor_file->comment);
	read_magic(cor_file->content);
	read_function(cor_file, cor_file->content);
	// ft_printf("%d\n", (unsigned char)cor_file->content[2196]);
	close(cor_file->fd);
}



int	main(int ac, char **av)
{
	if (ac == 2)
		unpack(av[1]);
	else
		unpack_error("Howto: ./unpack <file.cor>");
	// ft_printf("%d\n", hex_to_dec(strdup("0187")));
	return (0);
}
//
// 0B 68 01 01 87 00 01
// 0B 68 01 01 8F 00 01
// 0B 68 01 01 90 00 01
// 0B 68 01 00 57 00 01
// 0B 68 01 01 8D 00 01
// 0B 68 01 01 86 00 09
// 0B 68 01 01 7F 00 11
// 0B 68 01 01 A5 00 01
// 0B 68 01 01 89 00 02
// 0B 68 01 01 CD 00 01
// 0B 68 01 01 C6 00 09
// 0B 68 01 01 98 00 01
// 02 90 00 00 00 00 10
// 0C 01 43
// 02 90 00 00 00 00 02
// 02 90 00 00 00 00 10
// 01 00 4A CD C7
// 03 70 02 FF E8
// 03 70 02 FF DF
// 03 70 02 FF D6
// 03 70 02 FF CD
// 03 70 02 FF C4
// 03 70 02 FF BB
// 03 70 02 FF B2
// 03 70 02 FF A9
// 03 70 02 FF A0
// 03 70 02 FF 97
// 03 70 02 FF 8E
// 03 70 02 FF 85
// 03 70 02 FF 7C
// 03 70 02 FF 73
// 03 70 02 FF 6A
// 03 70 02 FF 61
// 03 70 02 FF 58
// 03 70 02 FF 4F
// 03 70 02 FF 46
// 03 70 02 FF 3D
// 03 70 02 FF 34
// 03 70 02 FF 2B
// 03 70 02 FF 22
// 03 70 02 FF 19
// 03 70 02 FF 10
// 03 70 02 FF 07
// 03 70 02 FE FE
// 03 70 02 FE F5
// 03 70 02 FE EC
// 03 70 02 FE E3
// 03 70 02 FE DA
// 03 70 02 FE D1
// 03 70 02 FE C8
// 03 70 02 FE BF
// 03 70 02 FE B6
// 03 70 02 FE AD
// 03 70 02 FE A4
// 03 70 02 FE 9B
// 03 70 02 FE 92
// 03 70 02 FE 89
// 03 70 02 FE 80
// 03 70 02 FE 77
// 03 70 02 FE 6E
// 03 70 02 FE 65
// 03 70 02 FE 5C
// 03 70 02 FE 53
// 03 70 02 FE 4A
// 03 70 02 FE 41
// 03 70 02 FE 38
// 03 70 02 FE 2F
// 03 70 02 FE 26
// 03 70 02 FE 1D
// 03 70 02 FE 14
// 03 70 02 FE 0B
// 03 70 02 FE 02
// 09 FE E8
// 01 00 40 B0 3F
// 0C FF FB
// 02 90 00 00 00 00 10
// 01 00 34 86 7E
// 09 FF FB
// 01 00 41 EC A7
// 09 00 03
// 0C FF F8
// 01 00 42 0E 4A
// 0C 00 5E
// 01 00 33 E5 A3
// 0C 00 2F
// 01 00 46 0B CF
// 0C 00 84
// 02 90 00 00 00 00 02
// 02 90 0F 03 70 03 03
// 02 90 00 00 00 00 10
// 01 00 4B 3B 77
// 02 90 00 00 00 00 10
// 09 00 78
// 01 00 42 42 46
// 0C FE 74
// 02 90 0F 03 70 03 02
// 02 90 17 03 70 03 03
// 02 90 00 00 00 00 10
// 02 90 00 00 00 00 10
// 09 00 51
// 01 00 40 AE A5
// 0C FF 98
// 01 00 3E 75 62
// 0C FF 6E
// 02 90 FF FF 01 00 02
// 02 90 1A 03 70 03 03
// 02 90 00 00 00 00 10
// 02 90 00 00 00 00 10
// 02 90 00 00 00 00 10
// 09 00 1B
// 02 90 03 70 02 00 02
// 02 90 13 03 70 03 03
// 02 90 00 00 00 00 10
// 09 00 03
// 03 70 02 00 0F
// 03 70 03 FF FF
// 01 00 00 00 00
