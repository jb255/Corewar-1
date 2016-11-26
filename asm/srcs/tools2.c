/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 03:10:02 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/19 03:12:08 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				init_env(t_env *e)
{
	e->name = NULL;
	e->comment = NULL;
	e->name_file = NULL;
	e->head = NULL;
	e->tail = NULL;
	e->suite = 0;
	e->y_line = 0;
	e->nb_tab = 16;
	e->method_position = 0;
}

char				*parsename(char *argv)
{
	int			a;
	int			b;
	int			c;
	char		*name_file;

	a = ft_strlen(argv);
	if ((a - 2) > 0 && (argv[a - 2] != '.' || argv[a - 1] != 's'))
		return (NULL);
	b = a;
	while (a && argv[a] != '/')
		a--;
	while (b && argv[b] != '.')
		b--;
	a = (argv[a] == '/' ? a + 1 : a);
	name_file = (char *)malloc(b - a + 5);
	c = -1;
	while (a <= b)
		name_file[++c] = argv[a++];
	name_file[c] = '.';
	name_file[c + 1] = 'c';
	name_file[c + 2] = 'o';
	name_file[c + 3] = 'r';
	name_file[c + 4] = '\0';
	return (name_file);
}

unsigned char		calc_octet(unsigned int *nbr, unsigned int diviseur)
{
	int				a;
	int				b;
	unsigned char	total;

	a = 128;
	b = 8;
	total = 0;
	while (b > 0)
	{
		total += ((*nbr / diviseur) * a);
		*nbr %= diviseur;
		diviseur /= 2;
		a /= 2;
		b--;
	}
	return (total);
}

unsigned char		*cut_nbr(unsigned int nbr)
{
	unsigned char *tab;

	tab = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 5);
	if (!tab)
		ft_printf("malloc error\n");
	tab[0] = calc_octet(&nbr, 2147483648);
	tab[1] = calc_octet(&nbr, 8388608);
	tab[2] = calc_octet(&nbr, 32768);
	tab[3] = calc_octet(&nbr, 128);
	return (tab);
}

void				decoupage_nb(t_line *tmp)
{
	unsigned char *cut;

	cut = cut_nbr(tmp->intfo1[1]);
	if (tmp->intfo1[2] == 4)
		ft_printf("%-4d%-4d%-4d%-6d", cut[0], cut[1], cut[2], cut[3]);
	else if (tmp->intfo1[2] == 2)
		ft_printf("%-4d%-14d", cut[2], cut[3]);
	else if (tmp->intfo1[2] == 1)
		ft_printf("%-18d", cut[3]);
	cut = cut_nbr(tmp->intfo2[1]);
	if (tmp->intfo2[2] == 4)
		ft_printf("%-4d%-4d%-4d%-6d", cut[0], cut[1], cut[2], cut[3]);
	else if (tmp->intfo2[2] == 2)
		ft_printf("%-4d%-14d", cut[2], cut[3]);
	else if (tmp->intfo2[2] == 1)
		ft_printf("%-18d", cut[3]);
	cut = cut_nbr(tmp->intfo3[1]);
	if (tmp->intfo3[2] == 4)
		ft_printf("%-4d%-4d%-4d%d", cut[0], cut[1], cut[2], cut[3]);
	else if (tmp->intfo3[2] == 2)
		ft_printf("%-4d%d", cut[2], cut[3]);
	else if (tmp->intfo3[2] == 1)
		ft_printf("%d", cut[3]);
}
