/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:57:55 by vlancien          #+#    #+#             */
/*   Updated: 2016/11/15 22:16:10 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_2d_tab(char **tab, int size)
{
	int a;

	a = 0;
	if (tab == NULL)
		return ;
	while (tab[a] && tab[a][0] && (a < size - 1))
	{
		free(tab[a]);
		++a;
	}
	free(tab[a]);
	free(tab);
}

void			print_2d_tab(char **tab, int size)
{
	int a;

	a = 0;
	if (tab == NULL)
		return ;
	while (tab[a] && tab[a][0] && (a < size - 1))
	{
		ft_putendl(tab[a]);
		++a;
	}
	ft_putendl(tab[a]);
}

void	double_cote(char *str, char *error)
{
	int	a;

	a = 0;
	while (*str)
	{
		if (*str == '\"')
			a++;
		str++;
	}
	if (a != 2)
		asm_error(error);
}
void	name_comment(char *str, t_env *e)
{
	char	**tab;

	tab = ft_strsplit(str, '\"');
	if ((str[1] == 'n') && (str[2] == 'a') && (str[3] == 'm') && (str[4] == 'e'))
	{
		double_cote(str, "error in .name");
		e->name = ft_strdup(tab[1]);
		if (ft_strlen(e->name) > PROG_NAME_LENGTH)
		{
			printf("Champion name to long (Max lenght %d)\n", PROG_NAME_LENGTH);
			free_2d_tab(tab, 2);
			exit(-1);
		}
	}
	else if ((str[1] == 'c') && (str[2] == 'o') && (str[3] == 'm')
		&& (str[4] == 'm') && (str[5] == 'e') && (str[6] == 'n') && (str[7] == 't'))
	{
		double_cote(str, "error in .comment");
		e->comment = ft_strdup(tab[1]);
		if (ft_strlen(e->comment) > COMMENT_LENGTH)
		{
			printf("Champion comment to long (Max lenght %d)\n", COMMENT_LENGTH);
			free_2d_tab(tab, 2);
			exit(-1);
		}
	}
	free_2d_tab(tab, 2);
}

int		epur_str(char *str)
{
	int		nb_c;
	int		old;
	int		new;
	int		find;

	nb_c = 0;
	old = 0;
	new = 0;
	find = 0;
	while (str[old] && (str[old] == ' ' || str[old] == '\t'))
		old++;
	while (str[old])
	{
		if (str[old] != ' ' && str[old] != '\t')
		{
			str[new] = str[old];
			new++;
			old++;
		}
		while (str[old] && (str[old] == ' ' || str[old] == '\t'))
		{
			find = 1;
			old++;
		}
		if ((find == 1) && str[old])
		{
			find = 0;
			str[new] = ' ';
			new ++;
			nb_c++;
		}
	}
	str[new] = '\0';
	return nb_c;
}

int		is_command(char *str, t_env *e)
{
	int i;

	i = 0;

	while (i < 17)
	{
		//printf("%s == %s\n", str, e->op_tab[i].name);
		if (ft_strcmp(str, e->op_tab[i].name) == 0)
		{
			e->nb_tab = i;
			return (e->op_tab[i].nb_param);
		}
		i++;
	}
	e->nb_tab = 16;
	printf("Syntax error in line %d\n", e->y_line);
	exit(1);
	return (0);
}
void	other(char *str, t_env *e)
{
	char	**tab;
	int		nb_space;
	int		command;

	nb_space = epur_str(str);
	tab = ft_str_ext_split(str, "\t ,");
	// printf("%s =>> ", str);
	// printf("%d\n", nb_space);
	if (nb_space == 0)
	{
		// printf("label\n");
		push_tail_label(&e->head, &e->tail, tab[0]);
		return ;
	}
	command = is_command(tab[0], e);
	if (nb_space != command)
	{
		printf("Syntax error in line %d\n", e->y_line);
		exit(1);
	}
	else
		push_tail_method(&e->tail->line, tab, command, e);

}

void	stock_line(char *str, t_env *e)
{
	if ((str[0] == 0) || (str[0] == COMMENT_CHAR) || (str[0] == COMMENT_CHAR2))
	{
		printf("ligne vide ou # ou ;\n");
		free(str);
		e->suite = 0;
		return ;
	}
	else if (str[0] == '.')
		name_comment(str, e);
	else
		other(str, e);
}

void	open_line(char *fichier, t_env *e)
{
	char	*line;
	int		fd;

	fd = open(fichier, O_RDONLY);
	if (fd == -1)
		asm_error("open_error");
	while (get_next_line(fd, &line) == 1)
	{
		++e->y_line;
		stock_line(line, e);
	}
	if (close(fd) != 0)
		asm_error("close_error");
	printf("%s->%s\n", e->name, e->comment);
}

// Retire juste les deux points a la fin de chaque label de methode
void	trim_args(t_env *file)
{
	t_func	*tmp_func;
	t_line	*tmp_line;

	tmp_func = file->head;
	while (tmp_func)
	{
		tmp_func->label[ft_strlen(tmp_func->label) - 1] = 0;
		tmp_func = tmp_func->next;
	}
}

// Utilise dans labels_are_defined pour checker la validite d'un label !
void	check_single_label(t_line *line, t_func *func, int nb_info, t_env *env)
{
	char	*info;

	if (nb_info == 1 || nb_info == 2)
		info = nb_info == 1 ? line->info1 : line->info2;
	else
		info = line->info3;
	while (func != NULL && info && ft_strcmp(func->label, info + 2))
		func = func->next;
	if (nb_info == 1)
		line->intfo1[1] = get_method_pos(info + 2, env);
	if (nb_info == 2)
		line->intfo2[1] = get_method_pos(info + 2, env);
	if (nb_info == 3)
		line->intfo3[1] = get_method_pos(info + 2, env);
	if (func == NULL)
	{
		asm_error("Label not defined");
		exit (-1);
	}
}
	// off_t	lenght_file;
	// if ((lenght_file =  lseek(fd, 0, SEEK_END)) > CHAMP_MAX_SIZE) //a faire sur le binaire
		// asm_error("fichier trop long");

// Verifie si les labels appeles dans les methodes de l'asm sont bien definis quelque part
// dans le meme fichier
int		labels_are_defined(t_env *file)
{
	t_func	*tmpa_func;
	t_func	*tmpb_func;
	t_line	*tmp_line;

	tmpa_func = file->head;
	while (tmpa_func != NULL)
	{
		tmp_line = tmpa_func->line;
		while (tmp_line != NULL)
		{
			if (tmp_line->info1 && ft_parse_match("*:[a-z0-9_]+", tmp_line->info1 + 1))
				check_single_label(tmp_line, tmpb_func = file->head, 1, file);
			if (tmp_line->info2 && ft_parse_match("*:[a-z0-9_]+", tmp_line->info2 + 1))
				check_single_label(tmp_line, tmpb_func = file->head, 2, file);
			if (tmp_line->info3 && ft_parse_match("*:[a-z0-9_]+", tmp_line->info3 + 1))
				check_single_label(tmp_line, tmpb_func = file->head, 3, file);
			tmp_line = tmp_line->next;
		}
		tmpa_func = tmpa_func->next;
	}
	return (1);
}

int		check_param(int nb_tab, t_op op_tab[], char *info, int nb_param)
{
	char	byte;
	char	*reg;
	
	reg = ft_strnew(ft_strlen(LABEL_CHARS) + 3);
	ft_strcpy(reg, "[");
	reg[1] = LABEL_CHAR;
	ft_strcpy(reg + 2, LABEL_CHARS);
	ft_strcpy(reg + ft_strlen(LABEL_CHARS), "]+");
	byte = op_tab[nb_tab].params_types[nb_param];
	printf("BYTE = %d\n", byte);
	printf("+++ Info vaut ==> %s\n+++\tinfo[0] vaut : %c\n", info, info[0]);
	if (byte & T_REG)
	{
		if (ft_parse_match("r[0-9]+", info) && ft_atoi(info + 1) <= REG_NUMBER)
			return (1);
		else if (byte == T_REG)
			return (0);
	}
	if (byte & T_DIR)
	{
		if (info[0] == DIRECT_CHAR &&
				(ft_parse_match("[0-9]+", info + 1) || ft_parse_match(reg, info + 1)))
			return (1);
		else if (byte == T_DIR || byte == (T_DIR | T_REG))
			return (0);
	}
	if (ft_parse_match("[0-9]+", info[0] == '-' ? info + 1 : info))
	   return (1);
	free(reg);
	return (0);
}

int		params_correspond(t_env *file)
{
	t_func	*func;
	t_line	*line;

	func = file->head;
	while (func)
	{
		line = func->line;
		while (line)
		{
			if (!check_param(line->nb_tab, file->op_tab, line->info1, 0))
				asm_error("Error type, 1");
			if (line->info2 &&
					!check_param(line->nb_tab, file->op_tab, line->info2, 1))
				asm_error("Error type, 2");
			if (line->info3 &&
					!check_param(line->nb_tab, file->op_tab, line->info3, 2))
				asm_error("Error type, 3");
			line = line->next;
			printf("\n");
		}
		func = func->next;
	}
	return (1);
}

// Prend le nom du label en question, et l'env et renvoie la position du label en octet
int		get_method_pos(char *label_name, t_env *file)
{
	t_func	*func;
	t_line	*line;

	func = file->head;
	while (func && ft_strcmp(func->label, label_name))
		func = func->next;
	if (!func)
		asm_error("An unknown error occured");
	return (func->line->method_position);
}
