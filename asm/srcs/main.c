/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:59:13 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 00:20:24 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	little_to_big(unsigned int little)
{
	unsigned int	big;

	big = ((little >> 24 ) & 0xff) | ((little << 8) & 0xff0000) |
	((little >> 8) & 0xff00) | ((little << 24 )& 0xff000000);
	return (big);
}

void	cut_nbr_and_write(unsigned int nbr, int how_cut, int fd)
{
	unsigned char *tab;

	tab = (unsigned char *)ft_memalloc(sizeof (unsigned char) * 5);
	if (!tab)
		ft_printf("malloc error\n");
	tab[0] = calc_octet(&nbr, 2147483648);
	tab[1] = calc_octet(&nbr, 8388608);
	tab[2] = calc_octet(&nbr, 32768);
	tab[3] = calc_octet(&nbr, 128);
	if (how_cut == 4)
		write(fd, &tab[0], 1);
	if (how_cut >= 3)
		write(fd, &tab[1], 1);
	if (how_cut >= 2)
		write(fd, &tab[2], 1);
	if (how_cut >= 1)
		write(fd, &tab[3], 1);
}

void	write_binary2(t_line *head, int fd)
{
	t_line *tmp;

	tmp = head;
	while (tmp)
	{
		write(fd, &tmp->opcode, 1);
		if (tmp->encod)
			write(fd, &tmp->encod, 1);
		if (tmp->nb_info > 0)
			cut_nbr_and_write(tmp->intfo1[1], tmp->intfo1[2], fd);
		if (tmp->nb_info > 1)
			cut_nbr_and_write(tmp->intfo2[1], tmp->intfo2[2], fd);
		if (tmp->nb_info > 2)
			cut_nbr_and_write(tmp->intfo3[1], tmp->intfo3[2], fd);
		tmp = tmp->next;
	}
}

void	write_binary(t_func	*head, int fd)
{
	t_func *tmp;

	tmp = head;
	while (tmp)
	{
		write_binary2(tmp->line, fd);
		tmp = tmp->next;
	}
}

void				create_file(t_env *e)
{
	int			fd;
	header_t	header;

	
	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 2);
	ft_bzero(header.comment, COMMENT_LENGTH + 1);
	header.prog_size = little_to_big(e->method_position + e->method_total);
	header.magic = little_to_big(COREWAR_EXEC_MAGIC);
	ft_strncpy(header.prog_name ,e->name, PROG_NAME_LENGTH);
	ft_strncpy(header.comment ,e->comment, COMMENT_LENGTH);
	if ((fd = open(e->name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		ft_printf(" error open %s\n", e->name_file);
	write(fd, &header, sizeof(header));
	write_binary(e->head, fd);
	if (close(fd) != 0)
		asm_error("close_error_.cor");
}

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
	int a;
	int b;
	unsigned char total;

	a = 128;
	b = 8;
	total = 0;
	while (b > 0)
	{
		total += ((*nbr / diviseur) * a);
		*nbr %= diviseur;
		diviseur /= 2;
		a /= 2;
		b --;
	}
	return (total);
}

unsigned char		*cut_nbr(unsigned int nbr)
{
	unsigned char *tab;

	tab = (unsigned char *)ft_memalloc(sizeof (unsigned char) * 5);
	if (!tab)
		printf("malloc error\n");
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
		printf("%-4d%-4d%-4d%-6d", cut[0], cut[1], cut[2], cut[3]);
	else if (tmp->intfo1[2] == 2)
		printf("%-4d%-14d", cut[2], cut[3]);
	else if (tmp->intfo1[2] == 1)
		printf("%-18d", cut[3]);
	cut = cut_nbr(tmp->intfo2[1]);
	if (tmp->intfo2[2] == 4)
		printf("%-4d%-4d%-4d%-6d", cut[0], cut[1], cut[2], cut[3]);
	else if (tmp->intfo2[2] == 2)
		printf("%-4d%-14d", cut[2], cut[3]);
	else if (tmp->intfo2[2] == 1)
		printf("%-18d", cut[3]);
	cut = cut_nbr(tmp->intfo3[1]);
	if (tmp->intfo3[2] == 4)
		printf("%-4d%-4d%-4d%d", cut[0], cut[1], cut[2], cut[3]);
	else if (tmp->intfo3[2] == 2)
		printf("%-4d%d", cut[2], cut[3]);
	else if (tmp->intfo3[2] == 1)
		printf("%d", cut[3]);
}

void				print_all_info(t_line *head)
{
	t_line	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%-5d(%-3d) :        ", tmp->method_position,
				tmp->method_total);
		printf("%-10s%-18s%-18s%s\n", tmp->method, tmp->info1, tmp->nb_info > 1
				? tmp->info2 : "", tmp->nb_info > 2 ? tmp->info3 : "");
		printf("                    %-4d", tmp->opcode);
		if (tmp->encod)
			printf("%-6d", tmp->encod);
		else
			printf("%-7c", 0);
		decoupage_nb(tmp);
		printf("\n                    %-4d",tmp->opcode);
		if (tmp->encod)
			printf("%-6d", tmp->encod);
		else
			printf("%-7c", 0);
		if (tmp->nb_info == 1)
			printf("%-18d\n\n", tmp->intfo1[1]);
		else if (tmp->nb_info == 2)
			printf("%-18d%-18d\n\n", tmp->intfo1[1], tmp->intfo2[1]);
		else	
			printf("%-18d%-18d%d\n\n", tmp->intfo1[1], tmp->intfo2[1],
					tmp->intfo3[1]);
		tmp = tmp->next;
	}
}

void				print_all(t_func *head)
{
	t_func	*tmp;

	tmp = head;
	if (tmp->line)
		while (tmp != NULL)
		{
			printf("%-11d:    ", tmp->line->method_position);
			printf("%s:\n", tmp->label);
			print_all_info(tmp->line);
			tmp = tmp->next;
		}
}

int					main(int argc, char **argv)
{
	t_env		e;

	if (argc < 2)
		asm_error("Usage: ./asm <sourcefile.s>");
	init_env(&e);
	if (!(e.name_file = parsename(argv[1])))
		asm_error("asm: wrong file extension!");
	printf("%s\n", e.name_file);
	fille_op_tab(&e);
	open_line(argv[1], &e);
	trim_args(&e);
	labels_are_defined(&e);
	params_correspond(&e);
	create_file(&e);
	print_all(e.head);
	return (0);
}
