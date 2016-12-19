/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:37:17 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/19 20:11:47 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "n_curse.h"

void	(*g_func_process[16])(t_env*, int, t_type_func) = {live_func, ld_func,
	st_func, add_func, sub_func, and_func, or_func, xor_func, zjump_func,
	ldi_func, sti_func, fork_func, lld_func, lldi_func, lfork_func, aff_func};

void			apply_func(t_env *e, int xproc, t_type_func list)
{
	if (list.func >= 1 && list.func <= 16)
		g_func_process[list.func - 1](e, xproc, list);
}

t_type_func		error_opsize(char *op_size, t_type_func list)
{
	list.func = -1;
	list.error = -1;
	free(op_size);
	return (list);
}

t_type_func		op_size_analys(t_type_func list,
	int x, int index, char *op_size)
{
	if (op_size[index] == '0' && op_size[index + 1] == '1' && (list.size += 1))
		list.type[x].t_reg++;
	else if (op_size[index] == '1'
	&& op_size[index + 1] == '0' && (list.size += 4))
	{
		list.type[x].t_dir++;
		if (list.func == 10 || list.func == 11 || list.func == 14)
			list.size -= 2;
	}
	else if (op_size[index] == '1' && op_size[index + 1] == '1' &&
	(list.size += 2))
		list.type[x].t_ind++;
	return (list);
}

t_type_func		check_jump(t_env *e, char *op_size, int func)
{
	int			index;
	int			x;
	t_type_func	list;

	index = 0;
	x = 0;
	ft_memset(&list, 0, sizeof(t_type_func));
	if (!ft_strcmp("00000000", op_size))
		return (error_opsize(op_size, list));
	if (ft_strlen(op_size) != 8)
		vm_error("Erreur de champion");
	list.func = func;
	list.size = 2;
	while (op_size[index] != '\0' && e->op[func - 1].nb_param > x)
	{
		// ft_printf("List size = %d\n", list.size);
		list = op_size_analys(list, x, index, op_size);
		index += 2;
		x++;
	}
	free(op_size);
	return (list);
}

int				octet_precision(char *hex, int octet)
{
	int		result;
	int		nb;
	char	test2[3];

	nb = 0;
	if (octet == 1)
		nb = 2;
	else if (octet == 2)
		nb = 4;
	else if (octet == 3)
		nb = 6;
	test2[0] = *(hex + nb);
	test2[1] = *(hex + (nb + 1));
	test2[2] = '\0';
	result = (short int)hex_to_dec(test2);
	return (result);
}

void			write_from_x(t_env *e, int from, int data, int octet)
{
	char	*hex;
	int		x;

	hex = NULL;
	(void)e;
	hex = ft_sprintf("%08x", data);
	while (octet > 0)
	{
		x = (from + (4 - octet)) % MEM_SIZE;
		x = x < 0 ? MEM_SIZE + x : x;
		tab[x] = octet_precision(hex, 4 - octet);
		octet--;
	}
	if (hex != NULL)
		free(hex);
}
