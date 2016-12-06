/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjump.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:24:29 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/06 13:39:14 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

// Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
// Elle prend toujours un index (IND_SIZE) et fait un saut à cet index si le carry est à un.
// Si le carry est nul, zjmp ne fait rien mais consomme le même temps.
// zjmp %23 met, si carry == 1, (PC + (23 % IDX_MOD)) dans le PC.
// l n’y a jamais eu, n’y a pas, et n’y aura jamais d’octet de codage des paramètres
// derrière cette opération dont l’opcode est de 9. Elle prendra un index, et fait un
// saut à cette adresse si le carry est à 1.
int		check_zjump(t_env *e, int xproc, t_type_func list)
{
	// ft_putstr_fd("Check_zjump -- Fonction\n", e->fd);
	(void)xproc;
	(void)list;
	(void)e;
	return (1);
}

void	zjump_func(t_env *e, int xproc, t_type_func list)
{
	char	*jump_to;

	(void)list;
	jump_to = get_x_from_position(e, e->process[xproc].position + 1, e->process[xproc].position + 3);
	// ft_printf_fd(e->fd, "Check_zjump process %d -- Jump to %d\n", xproc, (e->process[xproc].position + (short int)hex_to_dec(jump_to)) % IDX_MOD);
	// if (e->process[xproc].carry)
		e->process[xproc].position = (e->process[xproc].position + (short int)hex_to_dec(jump_to)) % IDX_MOD;
	// else
	// 	e->process[xproc].position = (e->process[xproc].position + list.size) % MEM_SIZE;
	free(jump_to);
}
