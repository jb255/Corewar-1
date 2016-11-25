/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 04:07:26 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/25 11:18:43 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_curse.h"
#include "function.h"


// • st : Prend un registre et un registre ou un indirect,
// et stocke la valeur du registre vers le second paramètre.
// Son opcode est 0x03. Par exemple, st r1, 42 stocke la valeur de r1 à l’adresse
// (PC + (42 % IDX_MOD))
// void	write_from_x(t_env *e, int from, int data, int xproc)
// {
// 	int		index;
// 	char	*hex;
// 	int		x;
//
// 	(void)e;
// 	(void)from;
// 	x = from;
// 	hex = dec_to_hex(data, NULL, intlen(data, 10));
// 	index = ft_strlen(hex);
// 	printf("->>>%s<----From{%d}Size{%d}\n", hex, from, index);
// 	while (x < from + index)
// 	{
// 		tab[x] = *hex;
// 		tab2[x] = e->process[xproc]->id_player;
// 		hex++;
// 		x++;
// 	}
// }
//
void	st_func(t_env *e, int xproc, t_type_func list)
{
	// char		*hex = NULL;
	int				reg = 0;
	int			regist = 0;

	(void)e;
	(void)list;
	(void)xproc;

	if (list.type[0].t_reg)
		reg = tab[e->process[xproc]->position + 2];
	printf("ST FUNC reg[%d]\n", reg);
	if (list.type[0].t_reg && list.type[1].t_reg)
		regist = e->process[xproc]->reg[tab[e->process[xproc]->position + 3]];
	else if (list.type[0].t_reg && list.type[1].t_ind)
	{
		unsigned int	x;
		int				index;
		char			*result = "";
		char			*name = NULL;

		index = 3;
		// printf("IND[%d][%s]\n", tab[e->process[xproc]->position + 3], dec_to_hex(tab[e->process[xproc]->position + 3], NULL, intlen(tab[e->process[xproc]->position + 3], 10)));
		// printf("IND[%d][%s]\n", tab[e->process[xproc]->position + 4], dec_to_hex(tab[e->process[xproc]->position + 4], NULL, intlen(tab[e->process[xproc]->position + 4], 10)));
		while (index < 5)
		{
			x = tab[e->process[xproc]->position + index];
			name = dec_to_hex(x, NULL, intlen(x, 10));
			result = ft_strjoin(result, strdup(name));
			if (result == NULL)
				vm_error("fe");
			index++;
		}
		regist = hex_to_dec(result);
	}
	if (!list.type[0].t_reg || (!list.type[1].t_reg && !list.type[1].t_ind))
		e->process[xproc]->jumptodo = 2;
	else
	{
		printf("VALEUR DU REGISTRE {%d}\n", e->process[xproc]->reg[reg]);
		// write_from_x(e, (e->process[xproc]->addr_pc + (regist % (IDX_MOD))), regist, xproc);
		printf("DATA ADDR{%d}\n", e->process[xproc]->addr_pc);
		// printf("DATA ADDR{%d}\n", (e->process[xproc]->addr_pc + (regist % IDX_MOD)));
		tab[(e->process[xproc]->addr_pc + (regist % IDX_MOD))] = 255;
		tab[(e->process[xproc]->addr_pc + (regist % IDX_MOD))+1] = 255;
		tab[(e->process[xproc]->addr_pc + (regist % IDX_MOD))+2] = 255;
		tab[(e->process[xproc]->addr_pc + (regist % IDX_MOD))+3] = 255;
	}
	// printf("REGISTRE ST %s et %d\n", reg, regist);

}
