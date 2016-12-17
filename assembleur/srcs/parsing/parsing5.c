/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 00:06:22 by mlevieux          #+#    #+#             */
/*   Updated: 2016/11/20 00:06:23 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		valid_name_comment(char *str, int code)
{
	int	i;
	int j;

	i = (code == 1) ? 5 : 8;
	while (str[i] != 0 && (str[i] == '\t' || str[i] == ' '))
		i += 1;
	if (str[i] != '\"')
		asm_error(ft_strjoin("Trailing characters before ",
			ft_strjoin(code == 1 ? "name : " : "comment : ", &str[i])));
	j = i;
	i += 1;
	while (str[i] != 0 && str[i] != '\"')
		i += 1;
	if (str[i] == 0)
		asm_error(ft_strjoin("Missing quotation mark to end ",
			ft_strjoin(code == 1 ? "name : " : "comment : ", &str[i])));
	i += 1;
	while (str[i] != 0 && (str[i] == '\t' || str[i] == ' '))
		i += 1;
	if (str[i] != 0 && str[i] != '#')
		asm_error(ft_strjoin("Trailing characters after ",
			ft_strjoin(code == 1 ? "name : " : "comment : ", &str[i])));
	return (1);
}

int		get_method_pos(char *label_name, t_env *file)
{
	t_func	*func;

	func = file->head;
	while (func && (!func->label || ft_strcmp(func->label, label_name)))
		func = func->next;
	if (!func)
		asm_error("An unknown error occured");
	return (func->position);
}

void	trim_args(t_env *file)
{
	t_func	*tmp_func;

	tmp_func = file->head;
	while (tmp_func)
	{
		if (tmp_func->label != NULL &&
			tmp_func->label[ft_strlen(tmp_func->label) - 1] == ':')
			tmp_func->label[ft_strlen(tmp_func->label) - 1] = 0;
		tmp_func = tmp_func->next;
	}
}

int		is_command(char *str, t_env *e)
{
	int i;

	i = 0;
	if (!ft_strcmp(str, ":"))
		return (0);
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
