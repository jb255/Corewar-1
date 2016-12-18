/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <jaustry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 14:45:30 by jaustry           #+#    #+#             */
/*   Updated: 2016/12/18 21:41:09 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

t_type_func	op_size_analys(char *op_size, int index, t_type_func list, int x)
{
	if (op_size[index] == '0' && op_size[index + 1] == '1' && (list.size += 1))
		list.type[x].t_reg++;
	else if (op_size[index] == '1' && op_size[index + 1] == '0'
	&& (list.size += 4))
	{
		list.type[x].t_dir++;
		if (list.func == 10 || list.func == 11 || list.func == 13)
			list.size -= 2;
	}
	else if (op_size[index] == '1' && op_size[index + 1] == '1'
	&& (list.size += 2))
		list.type[x].t_ind++;
	return (list);
}

t_type_func	check_jump(t_file *cor, char *op_size, int func)
{
	int			index;
	int			x;
	t_type_func	list;

	index = 0;
	x = 0;
	ft_memset(&list, 0, sizeof(t_type_func));
	if (ft_strlen(op_size) != 8)
		unpack_error("Error file.");
	list.size = 2;
	list.func = func;
	while (op_size[index] != '\0' && cor->op[func].nb_param > x)
	{
		list = op_size_analys(op_size, index, list, x);
		index += 2;
		x++;
	}
	free(op_size);
	return (list);
}

int			special_func(int func)
{
	if (func == 12 || func == 15)
		return (3);
	else if (func == 1)
		return (5);
	else if (func == 9 || func == 16)
		return (3);
	ft_printf("An error occured at this value ->%d<-\n", func);
	exit(1);
	return (0);
}
