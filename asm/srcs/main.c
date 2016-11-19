/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:59:13 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/19 04:41:25 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				print_all_info2(t_line *tmp)
{
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
		printf("\n                    %-4d", tmp->opcode);
		print_all_info2(tmp);
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
