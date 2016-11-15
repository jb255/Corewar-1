/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:59:13 by vlancien          #+#    #+#             */
/*   Updated: 2016/10/20 17:15:45 by vlancien         ###   ########.fr       */
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

void	create_file(t_env *e)
{
	int			fd;
	header_t	header;

	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header.comment, COMMENT_LENGTH + 1);

	header.prog_size = 0; // a calculer

	header.magic = little_to_big(COREWAR_EXEC_MAGIC);
	ft_strncpy(header.prog_name ,e->name,PROG_NAME_LENGTH);
	ft_strncpy(header.comment ,e->comment, COMMENT_LENGTH);
	if ((fd = open(e->name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		ft_printf(" error open %s\n", e->name_file);
	write(fd, &header, sizeof(header));

	if (close(fd) != 0)
		asm_error("close_error_.cor");
}

void	init_env(t_env *e)
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

char	*parsename(char *argv)
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
		// printf("%u %u\n", *nbr, diviseur);
		total += ((*nbr / diviseur) * a);
		*nbr %= diviseur;
		diviseur /= 2;
		a /= 2;
		b --;
	}
	return (total);
}

unsigned char		*cut_nbr(unsigned nbr) // cree un tab de 4 char   
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

void	decoupage_nb(t_line *tmp)
{
	unsigned char *cut;

	cut = cut_nbr(tmp->intfo1[1]);
	printf("%d %d %d %d ", cut[0], cut[1], cut[2], cut[3]);
	cut = cut_nbr(tmp->intfo2[1]);
	printf("%d %d %d %d ", cut[0], cut[1], cut[2], cut[3]);
	cut = cut_nbr(tmp->intfo3[1]);
	printf("%d %d %d %d ", cut[0], cut[1], cut[2], cut[3]);

}

void	print_all_info(t_line *head)
{
	t_line	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%d    (%d  ) :        ", tmp->method_position,
			tmp->method_total);
		printf("%s       %s     %s      %s\n", tmp->method,
			tmp->info1, tmp->info2, tmp->info3);		
		printf("                    %d  ",tmp->opcode);
		if (tmp->encod)
			printf("%d ", tmp->encod);
		decoupage_nb(tmp);
		printf("\n");
		printf("                    %d  ",tmp->opcode);
		if (tmp->encod)
			printf("%d ", tmp->encod);
		printf("     %d         %d       %d", tmp->intfo1[1], tmp->intfo2[1], tmp->intfo3[1]);
		printf("\n");
		printf("\n");
		tmp = tmp->next;
	}
}
void	print_all(t_func *head)
{
	t_func	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("%d          :    ", tmp->line->method_position);
		printf("%s\n", tmp->label);
		print_all_info(tmp->line);
		tmp = tmp->next;
	}
}

int		main(int argc, char **argv)
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
