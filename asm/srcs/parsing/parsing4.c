#include "parsing.h"

void	check_single_label(t_line *line, t_func *func, int nb_info, t_env *env)
{
	char	*info;

	if (nb_info == 1 || nb_info == 2)
		info = nb_info == 1 ? line->info1 : line->info2;
	else
		info = line->info3;
	while (func != NULL && info && ft_strcmp(func->label, info + 2))
		func = func->next;
	if (func == NULL)
	{
		printf("Call to undefined label \"%s\" at line %d\n", info + 2, line->line_in_file);
		exit (-1);
	}
	if (nb_info == 1)
		line->intfo1[1] = get_method_pos(info + 2, env) - line->method_position;
	if (nb_info == 2)
		line->intfo2[1] = get_method_pos(info + 2, env) - line->method_position;
	if (nb_info == 3)
		line->intfo3[1] = get_method_pos(info + 2, env) - line->method_position;
}