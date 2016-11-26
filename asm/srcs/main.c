/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 12:59:13 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/26 05:32:42 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				print_all_info2(t_line *tmp)
{
	if (tmp->encod)
		ft_printf("%-6d", tmp->encod);
	else
		ft_printf("%-7c", 0);
	if (tmp->nb_info == 1)
		ft_printf("%-18d\n\n", tmp->intfo1[1]);
	else if (tmp->nb_info == 2)
		ft_printf("%-18d%-18d\n\n", tmp->intfo1[1], tmp->intfo2[1]);
	else
		ft_printf("%-18d%-18d%d\n\n", tmp->intfo1[1], tmp->intfo2[1],
				tmp->intfo3[1]);
}

void				print_all_info(t_line *head)
{
	t_line	*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		ft_printf("%-5d(%-3d) :        ", tmp->method_position,
				tmp->method_total);
		ft_printf("%-10s%-18s%-18s%s\n", tmp->method, tmp->info1, tmp->nb_info
			> 1 ? tmp->info2 : "", tmp->nb_info > 2 ? tmp->info3 : "");
		ft_printf("                    %-4d", tmp->opcode);
		if (tmp->encod)
			ft_printf("%-6d", tmp->encod);
		else
			ft_printf("%-7c", 0);
		decoupage_nb(tmp);
		ft_printf("\n                    %-4d", tmp->opcode);
		print_all_info2(tmp);
		tmp = tmp->next;
	}
}

void				print_all(t_env *e)
{
	t_func	*tmp;

	tmp = e->head;
	ft_printf("Dumping annoted program on standard output\nProgram size : ");
	ft_printf("%d bytes\nName : \"", e->method_position + e->method_total);
	ft_printf("%s\"\nComment : \"%s\"\n\n", e->name, e->comment);
	if (tmp->line)
		while (tmp != NULL)
		{
			ft_printf("%-11d:    ", tmp->position);
			ft_printf("%s:\n", tmp->label);
			print_all_info(tmp->line);
			tmp = tmp->next;
		}
}

int					main(int argc, char **argv)
{
	t_env		e;

	if (argc < 2)
	{
		ft_printf("Usage: ./asm <sourcefile.s>\n");
		ft_printf("-a : Instead of creating a .cor file, outputs a stripped ");
		ft_printf("and annotated version of the code to the standard output\n");
		exit(-1);
	}
	init_env(&e);
	if (!(e.name_file = parsename(argv[argc - 1])))
		asm_error("asm: wrong file extension!");
	fille_op_tab(&e);
	open_line(argv[argc - 1], &e);
	trim_args(&e);
	labels_are_defined(&e);
	params_correspond(&e);
	create_file(&e);
	if (!ft_strcmp(argv[1], "-a"))
		print_all(&e);
	else
		ft_printf("Writing output to program\n");
	return (0);
}
