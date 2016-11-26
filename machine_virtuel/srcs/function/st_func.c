/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 04:07:26 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 07:14:41 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"

// • st : Prend un registre et un registre ou un indirect,
// et stocke la valeur du registre vers le second paramètre.
// Son opcode est 0x03. Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
// (PC + (42 % IDX_MOD))

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
		tab[(from + (4 - octet)) % MEM_SIZE] = octet_precision(hex, 4 - octet);
		octet--;
	}
}

void	st_func(t_env *e, int xproc, t_type_func list)
{
	char			*result = "";
	int				reg = 0;
	int			regist = 0;

	printf("ST FUNC reg[%d]\n", reg);
	if (list.type[0].t_reg)
		reg = tab[e->process[xproc].position + 2];
	if (list.type[0].t_reg && list.type[1].t_reg){
		regist = e->process[xproc].reg[tab[e->process[xproc].position + 3]];
		e->process[xproc].reg[reg] = regist;
	}
	else if (list.type[0].t_reg && list.type[1].t_ind)
	{
		result = get_x_from_position(e, xproc, 3, 5);
		regist = hex_to_dec(result);
		write_from_x(e, (e->process[xproc].addr_pc + (regist % (IDX_MOD))), e->process[xproc].reg[reg], 4);
	}
	if (!list.type[0].t_reg || (!list.type[1].t_reg && !list.type[1].t_ind))
		e->process[xproc].jumptodo = 2;
}
