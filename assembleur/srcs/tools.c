/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <jaustry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:25:20 by jaustry           #+#    #+#             */
/*   Updated: 2016/12/18 22:23:02 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			cut_nbr_and_write(unsigned int nbr, int how_cut, int fd)
{
	unsigned char tab[4];

	tab[0] = (unsigned char)calc_octet(&nbr, 2147483648);
	tab[1] = (unsigned char)calc_octet(&nbr, 8388608);
	tab[2] = (unsigned char)calc_octet(&nbr, 32768);
	tab[3] = (unsigned char)calc_octet(&nbr, 128);
	if (how_cut == 4)
		write(fd, &tab[0], 1);
	if (how_cut >= 3)
		write(fd, &tab[1], 1);
	if (how_cut >= 2)
		write(fd, &tab[2], 1);
	if (how_cut >= 1)
		write(fd, &tab[3], 1);
}

void			free_all(t_line *to_free)
{
	free(to_free->info1);
	free(to_free->info2);
	free(to_free->info3);
	free(to_free->method);
	free(to_free);
}

void			write_binary2(t_line *head, int fd)
{
	t_line *tmp;
	t_line *to_free;

	tmp = head;
	while (tmp)
	{
		to_free = tmp;
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
		if (to_free)
			free_all(to_free);
	}
}

void			write_binary(t_func *head, int fd)
{
	t_func *tmp;
	t_func *to_free;

	tmp = head;
	while (tmp)
	{
		to_free = tmp;
		write_binary2(tmp->line, fd);
		tmp = tmp->next;
		if (to_free)
		{
			free(to_free->label);
			free(to_free);
		}
	}
}

void			create_file(t_env *e)
{
	int			fd;
	t_header	header;

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
	free(e->name_file);
	free(e->name);
	free(e->comment);
}
