/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viko <viko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:21:41 by viko              #+#    #+#             */
/*   Updated: 2016/12/19 19:19:32 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unpack.h>

int		writememnb(int nb, int first)
{
	if (first && nb < 16)
		write(1, "0", 1);
	if (nb < 10)
		ft_putchar(nb + 48);
	else if (nb >= 10 && nb < 16)
		ft_putchar(nb + 55);
	else
	{
		writememnb(nb / 16, 0);
		writememnb(nb % 16, 0);
	}
	return (0);
}

char	*get_x(t_file *cor, int from, int at)
{
	char			*result;
	char			*name;
	int				index;
	char			*tmp;

	result = "";
	index = from;
	while (index != at)
	{
		name = ft_sprintf("%02x", (unsigned char)cor->content[index]);
		tmp = result;
		result = ft_strjoin(result, name);
		index++;
		if (ft_strlen(tmp) != 0)
			free(tmp);
		free(name);
	}
	return (result);
}

int		todec(char *str)
{
	int		result;

	result = hex_to_dec(str);
	free(str);
	return (result);
}

void	print_args(t_type_a arg, int *index, int func, t_file *cor)
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
		if (func == 10 || func == 11 || func == 13 || func == 14)
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

void	get_args(t_file *cor, t_type_func list, int index)
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
