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

#include "../../includes/corewar.h"

int		is_command(char *str, t_env *e)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(str, e->op_tab[i].name) == 0)
		{
			e->nb_tab = i;
			return (e->op_tab[i].nb_param);
		}
		i++;
	}
	e->nb_tab = 16;
	ft_printf("Error line %d, instruction \"%s\"", e->y_line, str);
	ft_printf(" does not exist\n");
	exit(-1);
	return (0);
}

int		ft_match_command(int command, char **tab, int line, char *inst)
{
	int		i;

	i = 0;
	while (tab[i] && tab[i][0] != COMMENT_CHAR &&
				tab[i][0] != COMMENT_CHAR2)
		i++;
	i -= 1;
	if (!tab[i])
		i -= 1;
	if (i != command)
	{
		ft_printf("Error line %d, instruction \"%s\" requires", line, inst);
		ft_printf(" %d arguments, %d were given\n", command, i);
		exit(-1);
	}
	return (1);
}

void	free_split(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	syntax_error(t_env *e)
{
	ft_printf("Unknown syntax error line %d\n", e->y_line);
	exit(-1);
}

void	other(char *str, t_env *e)
{
	char	**tab;
	int		nb_space;
	int		command;
	int		flag;

	nb_space = epur_str(str);
	verify_comma_continuity(str, e->y_line);
	tab = ft_str_ext_split(str, "\t ,");
	flag = 0;
	if (tab[0][ft_strlen(tab[0]) - 1] == ':')
	{
		push_tail_label(&e->head, &e->tail, tab[0], e);
		flag = 1;
		if (tab + 1 == NULL)
			return ;
	}
	command = is_command(tab[flag], e);
	if (tab[flag] != NULL && (flag == 0 ||
		ft_match_command(command, tab + flag, e->y_line, tab[flag])))
	{
		if (e->tail == NULL)
			push_tail_label(&e->head, &e->tail, NULL, e);
		push_tail_method(&e->tail->line, tab + flag, command, e);
	}
	else if (flag == 0)
		syntax_error(e);
	free_split(tab);
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
	if (pm(tmp, str) || pm(tmp2, str) ||
			(str[0] == 0) || (str[0] == COMMENT_CHAR) ||
			(str[0] == COMMENT_CHAR2) || !str)
	{
		free(str);
		free(tmp);
		free(tmp2);
		e->suite = 0;
		return ;
	}
	else if (str[0] == '.')
		name_comment(str, e);
	else
		other(str, e);
	free(tmp);
	free(tmp2);
	if (str && str[0])
		free(str);
}

int		check_line_content(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
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
		if (check_line_content(line))
			stock_line(line, e);
		else
			free(line);
		line = NULL;
	}
	free(line);
	if (close(fd) != 0)
		asm_error("close_error");
}
