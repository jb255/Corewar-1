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
