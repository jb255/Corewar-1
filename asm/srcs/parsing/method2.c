
#include "corewar.h"

int		coerence_str_optab(char *str, t_env *e)
{
	if ((str[0]) == 'r')
	{
		e->method_total += 1;
		return (1);
	}
	else if ((str[0]) == '%' && ((str[1] == ':') ||
		((ft_strlen(str) < 5) && str[1] != '0')))
	{
		e->method_total += 2;
		return (10);
	}
	else if ((str[0]) == '%')
	{
		e->method_total += 4;
		return (10);
	}
	else
	{
		e->method_total += 2;
		return (11);
	}
}