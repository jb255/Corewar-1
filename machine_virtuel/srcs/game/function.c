/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:37:17 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/29 18:29:49 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "n_curse.h"

void	(*g_func_process[5])(t_env*, int, t_type_func) = {live_func, ld_func, st_func, add_func, sub_func};

void		apply_func(t_env *e, int xproc, t_type_func list)
{
	if (list.func == 1 || list.func == 3 || list.func == 2 || list.func == 4 || list.func == 5)
		g_func_process[list.func - 1](e, xproc, list);
}

t_type_func check_jump(t_env *e, char *op_size)
{
	int			index;
	int			x;
	t_type_func	list;

	(void)e;
	index = 0;
	x = 0;
	ft_memset(&list, 0, sizeof(t_type_func));
	if (ft_strlen(op_size) != 8)
	{
		ft_putstr_fd("ERROR - check_jump op_size != 8 ->>", e->fd);
		ft_putstr_fd(op_size, e->fd);
		ft_putstr_fd("\n", e->fd);
	}
	list.size = 2;
	while (op_size[index] != '\0')
	{
		if (op_size[index] == '0' && op_size[index + 1] == '1'){
			list.type[x].t_reg++;
			list.size += 1;
		}
		else if (op_size[index] == '1' && op_size[index + 1] == '0'){
			list.type[x].t_dir++;
			list.size += 2;
		}
		else if (op_size[index] == '1' && op_size[index + 1] == '1'){
			list.type[x].t_ind++;
			list.size += 2;
		}
		index += 2;
		x++;
	}
	return (list);
}

int		octet_precision(char *hex, int octet)
{
	char	*test;
	int		nb;

	nb = 0;
	if (octet == 1)
		nb = 2;
	else if (octet == 2)
		nb = 4;
	else if (octet == 3)
		nb = 6;
	test = ft_strdup(hex + nb);
	test[2] = '\0';
	return (hex_to_dec(test));
}

void	write_from_x(t_env *e, int from, int data, int octet)
{
	char	*hex;

	(void)e;
	hex = ft_sprintf("%08x", data);
	while (octet > 0)
	{
		ft_printf_fd(e->fd, "Writing at %d, ->%02x base->%s\n", (from + (4 - octet)) % MEM_SIZE, tab[(from + (4 - octet)) % MEM_SIZE], hex);
		tab[(from + (4 - octet)) % MEM_SIZE] = octet_precision(hex, 4 - octet);
		octet--;
	}
}
