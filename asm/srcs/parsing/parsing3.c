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
	ft_printf("Syntax error in line %d\n", e->y_line);
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
	int		flag;

	printf("Entree %s\n", __FUNCTION__);

	nb_space = epur_str(str);
	printf("1\n");
	verify_comma_continuity(str, e->y_line);
	printf("2\n");
	tab = ft_str_ext_split(str, "\t ,");
	printf("3, line nb : %d, tab[0] = %s\n", e->y_line, tab[0]);
	flag = 0;
	if (tab[0][ft_strlen(tab[0]) - 1] == ':')
	{
		printf("4\n");
		push_tail_label(&e->head, &e->tail, tab[0], e);
		flag = 1;
		if (++tab == NULL)
			return ;
	}
	printf("5\n");
	command = is_command(tab[0], e);
	printf("6\n");
	if (flag == 0 && !ft_match_command(command, tab))
	{
		ft_printf("Syntax error in line %d, the string is : %s\n", e->y_line, str);
		exit(1);
	}
	else if (tab[0] != NULL)
	{
		if (e->tail == NULL)
			push_tail_label(&e->head, &e->tail, ft_strnew(0), e);
		push_tail_method(&e->tail->line, tab, command, e);
	}
	printf("Sortie %s\n", __FUNCTION__);
}

void	stock_line(char *str, t_env *e)
{
	char	*tmp;
	char	*tmp2;

	printf("Entree %s\n", __FUNCTION__);

	tmp = ft_strnew(7);
	ft_strcpy(tmp, "[\t ]+");
	tmp[5] = COMMENT_CHAR;
	tmp[6] = '*';
	tmp2 = ft_strdup(tmp);
	tmp2[5] = COMMENT_CHAR2;
	if (ft_parse_match(tmp, str) || ft_parse_match(tmp2, str) ||
			(str[0] == 0) || (str[0] == COMMENT_CHAR) ||
			(str[0] == COMMENT_CHAR2) || !str)
	{
		free(str);
		e->suite = 0;
		return ;
	}
	else if (str[0] == '.')
		name_comment(str, e);
	else
		other(str, e);
	free(tmp);
	printf("Sortie %s\n", __FUNCTION__);
	free(tmp2);
}

int		check_line_content(char *line)
{
	char	*tmp;

	tmp = line;
	while (*tmp)
	{
		if (*tmp != ' ' && *tmp != '\t')
			return (1);
		tmp++;
	}
	return (0);
}

void	open_line(char *fichier, t_env *e)
{
	char	*line;
	int		fd;

	printf("Entree %s\n", __FUNCTION__);
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
		asm_error("open_error");
	while (get_next_line(fd, &line) == 1)
	{
		++e->y_line;
		if(check_line_content(line))
			stock_line(line, e);
		else
			free(line);
	}
	free(line);
	if (close(fd) != 0)
		asm_error("close_error");
	printf("Sortie %s\n", __FUNCTION__);
}
