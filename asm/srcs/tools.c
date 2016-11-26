/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:25:20 by jaustry           #+#    #+#             */
/*   Updated: 2016/11/19 03:14:47 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	little_to_big(unsigned int little)
{
	unsigned int	big;

	big = ((little >> 24) & 0xff) | ((little << 8) & 0xff0000) |
	((little >> 8) & 0xff00) | ((little << 24) & 0xff000000);
	return (big);
}

void			cut_nbr_and_write(unsigned int nbr, int how_cut, int fd)
{
	unsigned char tab[4];

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

void			write_binary2(t_line *head, int fd)
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

void			write_binary(t_func *head, int fd)
{
	t_func *tmp;

	tmp = head;
	while (tmp)
	{
		write_binary2(tmp->line, fd);
		tmp = tmp->next;
	}
}

void			create_file(t_env *e)
{
	int			fd;
	header_t	header;

	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 2);
	ft_bzero(header.comment, COMMENT_LENGTH + 1);
	header.prog_size = little_to_big(e->method_position + e->method_total);
	header.magic = little_to_big(COREWAR_EXEC_MAGIC);
	ft_strncpy(header.prog_name, e->name, PROG_NAME_LENGTH);
	ft_strncpy(header.comment, e->comment, COMMENT_LENGTH);
	if ((fd = open(e->name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		ft_printf(" error open %s\n", e->name_file);
	write(fd, &header, sizeof(header));
	write_binary(e->head, fd);
	if (close(fd) != 0)
		asm_error("close_error_.cor");
}
