/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 04:07:26 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 00:19:12 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"


// • st : Prend un registre et un registre ou un indirect,
// et stocke la valeur du registre vers le second paramètre.
// Son opcode est 0x03. Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
// (PC + (42 % IDX_MOD))
void	write_from_x(t_env *e, int from, int data, int xproc)
{
	int		index;
	char	*hex;
	int		x;

	(void)e;
	(void)from;
	x = from;
	hex = dec_to_hex(data, NULL, intlen(data));
	index = ft_strlen(hex);
	printf("->>>%s<----From{%d}Size{%d}\n", hex, from, index);
	while (x < from + index)
	{
		tab[x] = *hex;
		tab2[x] = e->process[xproc]->id_player;
		hex++;
		x++;
	}
}

void	st_func(t_env *e, int xproc, int func)
{
	t_type_func	list;
	int			position;
	char		*hex = NULL;
	char		*reg = NULL;
	int			regist = 0;

	(void)func;
	position = e->process[xproc]->position;
	list = check_jump(e, hex_to_bin_quad(get_op_str(tab[(position + 2) % ((MEM_SIZE) * 2)], tab[(position + 3) % ((MEM_SIZE) * 2)])));
	if (list.type[0].t_reg)
		reg = get_opfrom_x(e, position + 4, position + 6);
	if (list.type[0].t_reg && list.type[1].t_reg){
		hex = get_opfrom_x(e, position + 6, position + 8);
		regist = e->process[xproc]->reg[ft_atoi(hex)];
	}
	else if (list.type[0].t_reg && list.type[1].t_ind) {
		hex = get_opfrom_x(e, position + 6, position + 10);
		regist = (int)hex_to_dec(hex);
	}
	if (!list.type[0].t_reg || (!list.type[1].t_reg && !list.type[1].t_ind))
		e->process[xproc]->jumptodo = 2;
	else
	{
		printf("VALEUR DU REGISTRE {%d}\n", e->process[xproc]->reg[ft_atoi(hex)]);
		write_from_x(e, (e->process[xproc]->addr_pc + (regist % (IDX_MOD))), regist, xproc);
		// printf("FAULT\n");

		// printf("VALUE TO ADD %d - %s\n", regist, dec_to_hex(regist, NULL, intlen(regist)));
		// printf("DATA ADDR{%d}\n", (e->process[xproc]->addr_pc + (regist % IDX_MOD)));
	}
	// printf("REGISTRE ST %s et %d\n", reg, regist);

}
