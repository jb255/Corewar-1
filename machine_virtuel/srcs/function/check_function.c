/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:59:38 by vlancien          #+#    #+#             */
/*   Updated: 2016/12/06 17:06:23 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <n_curse.h>
#include <function.h>

int		is_register_valid(t_env *e, int xproc, int position)
{
	char	*result;
	int		reg;

	reg = tab[(e->process[xproc].position + position) % (MEM_SIZE)];
	result = NULL;
	result = ft_sprintf("%02x", reg);
	reg = hex_to_dec(result);
	ft_printf_fd(e->fd, "+++Verification du registre reg.%d a la pos.%d hex.%02x++++++\n", reg, (e->process[xproc].position + position) % (MEM_SIZE), tab[(e->process[xproc].position + position) % (MEM_SIZE)]);
	free(result);
	if (reg > 0 && reg < 17)
		return (1);
	return (0);
}

void	name_process(t_env *e, char	*name)
{
	int		x;
	char	*tmp;

	tmp = NULL;
	x = 0;
	(void)name;
	while (x < e->active_players)
	{
		// if (!ft_strcmp(name, (tmp = ft_sprintf("%x", (e->players[x].id_player-1))))){
		// 	ft_printf_fd(e->fd, "(`'-._ Live for %s _.-'`)\n", e->players[x].name);
		// }
		x++;
		// free(tmp);
	}
}

char	*get_x_from_position(t_env *e, int from, int at)
{
	char			*result = "";
	char			*name;
	int				index;

	(void)e;
	if (from < 0)
		from = MEM_SIZE + from;
	index = from;
	while (index != at)
	{
		ft_printf_fd(e->fd, "--->Recherche a partir de %d a %d ->Actual n%d[%d] hex[%02x]\n", from, at, index,tab[index % MEM_SIZE], tab[index % MEM_SIZE]);
		name = ft_sprintf("%02x", tab[index % MEM_SIZE]);
		result = ft_strjoin(result, name);
		index++;
		if (index == MEM_SIZE)
			index = 0;
		free(name);
	}
	return (result);
}