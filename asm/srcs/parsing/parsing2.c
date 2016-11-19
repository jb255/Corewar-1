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