/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:43:13 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/19 04:00:07 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		is_command(char *str, t_env *e)
{
	int i;

	i = 0;
	while (i < 17)
	{
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

int		ft_match_command(int command, char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	i -= 1;
	if (i != command)
	{
		if (i < command)
			return (0);
		else if (tab[command + 1][0] != COMMENT_CHAR &&
				tab[command + 1][0] != COMMENT_CHAR2)
			return (0);
	}
	return (1);
}

void	other(char *str, t_env *e)
{
	char	**tab;
	int		nb_space;
	int		command;

	nb_space = epur_str(str);
	verify_comma_continuity(str, e->y_line);
	tab = ft_str_ext_split(str, "\t ,");
	if (nb_space == 0 && ft_strchr(tab[0], ':'))
	{
		push_tail_label(&e->head, &e->tail, tab[0], e->y_line);
		return ;
	}
	command = is_command(tab[0], e);
	if (!ft_match_command(command, tab))
	{
		printf("Syntax error in line %d\n", e->y_line);
		exit(1);
	}
	else
	{
		if (e->tail == NULL)
			push_tail_label(&e->head, &e->tail, ft_strnew(0), e->y_line);
		push_tail_method(&e->tail->line, tab, command, e);
	}
}

void	stock_line(char *str, t_env *e)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strnew(7);
	ft_strcpy(tmp, "[\t ]+");
	tmp[5] = COMMENT_CHAR;
	tmp[6] = '*';
	tmp2 = ft_strdup(tmp);
	tmp2[5] = COMMENT_CHAR2;
	if (ft_parse_match(tmp, str) || ft_parse_match(tmp2, str) ||
			(str[0] == 0) || (str[0] == COMMENT_CHAR) ||
			(str[0] == COMMENT_CHAR2))
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
	free(tmp);
	free(tmp2);
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
}
