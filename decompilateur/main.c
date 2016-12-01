/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlevieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 19:54:22 by mlevieux          #+#    #+#             */
/*   Updated: 2016/12/01 21:57:07 by mlevieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompile.h"
#include "time.h"

// Error codes :
// 1. No file given
// 2. Could not open file
// 3. Error reading file

// La fonction suivante sert juste a lire le fichier entier et a le mettre dans
// le champ 'brute_file' de data, elle set egalement les autres champs a leur
// equivalent NULL
t_data		*get_file_info(char *file_name)
{
	t_data	*res;
	int		fd;

	res = (t_data *)malloc(sizeof(t_data));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error(2);
	res->file_name = ft_strdup(file_name);
	res->brute_file = ft_strnew(CHAMP_MAX_SIZE);
	if ((res->content_size = read(fd, res->brute_file, CHAMP_MAX_SIZE)) == -1)
		error(3);
	res->pointer = 0;
	res->core_name = NULL;
	res->core_comment = NULL;
	res->content = NULL;
	res->len = NULL;
	res->nb_commands = 0;
	return (res);
}

// La fonction suivante est un simple strdup modifie pour palier au probleme cause
// par les zeros dans les chaines de bytes a copier d'une chaine a l'autre
// du coup elle a le meme exact comportement qu'un strdup a la difference
// qu'au lieu de copier jusqu'au zero elle copie len bytes
char		*ft_strndup(char *to_copy, size_t len)
{
	char	*res;

	if (to_copy == NULL)
		return (NULL);
	res = ft_strnew(len);
	while (--len - 1 > 0)
		res[len] = to_copy[len];
	return (res);
}

// Cette fonction s'occupe juste de sauter d'opcode en opcode
// et de remplir le champs 'content' de data avec les 'lignes' de bytecode
// a noter qu'aucune modification du contenu n'est faite ici!
void		parse_info(t_data *data)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = data->brute_file;
	i = get_name_and_comment(tmp, data);
	while (i < data->content_size)
	{
		j = next_command_size(&(tmp[i]));
		add_dim(data, ft_strsub(tmp, i, j - i + 1), j - i + 1);
		i = j + 1;
	}
	free(data->brute_file);
	data->brute_file = NULL;
	data->content_size = 0;
}

// La fonction suivante permet de reallouer, de copier et de rajouter un
// elements aux tableaux 'content' et 'len' automatiquement, un peu long en
// execution surement mais etant donne la taille maximum d'un champion
// on va en faire abstraction
void		add_dim(t_data *data, char *to_add, int len_str)
{
	int		i;
	char	**tmp;
	int		*tmp_int;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (data->nb_commands + 1));
	while (i < data->nb_commands)
	{
		tmp[i] = ft_strndup(data->content[i], data->len[i]);
		free(data->content[i]);
		i += 1;
	}
	tmp[i] = ft_strndup(to_add, len_str);
	free(to_add);
	free(data->content);
	data->content = tmp;
	data->nb_commands += 1;
	tmp_int = (int*)malloc(sizeof(int) * data->nb_commands);
	ft_memcpy(tmp_int, data->len, data->nb_commands - 1);
	tmp_int[data->nb_commands - 1] = len_str;
	free(data->len);
	data->len = tmp_int;
}

int			get_ocp_len(char *champ)
{
	int	size;

	size = 0;
	if (*champ << 2 & 000000001)
		size += 1;
	else if (*champ << 2 & 000000010)
		size += 2;
	else if (*champ << 2 & 000000011)
		size += 4;
	if (*champ << 4 & 000000001)
		size += 1;
	else if (*champ << 4 & 000000010)
		size += 2;
	else if (*champ << 4 & 000000011)
		size += 4;
	if (*champ << 6 & 000000001)
		size += 1;
	else if (*champ << 6 & 000000010)
		size += 2;
	else if (*champ << 6 & 000000011)
		size += 4;
	return (size);
}

int			get_spec_len(char *champ)
{
	if (*champ == 15)
		return (REG_SIZE);
	else
		return (DIR_SIZE);
}

int			next_command_size(char *champ)
{
	int		size;

	size = 1;
	if (*champ == 0 || *champ == 8 || *champ == 11 ||
			*champ == 14 || *champ == 15)
		size += get_spec_len(champ);
	else
		size += get_ocp_len(champ + 1);
	return (size);
}

char		*generate_label(void)
{
	time_t	t;
	char	nb_chars;
	char	*label;
	int		i;

	srand(time(NULL));
	nb_chars = MIN_CHAR_NUM + rand() % (MAX_CHAR_NUM - MIN_CHAR_NUM);
	label = ft_strnew(nb_chars);
	i = 0;
	while (i < nb_chars)
	{
		t = (time_t)clock();
		srand(t);
		label[i] = (char)((rand() % 26) + 98);
		i += 1;
	}
	return (label);
}

/* 
* * Le concept est plutot simple, on commence par verifier si le nombre de
** fichiers donnes en argument n'est pas nul, puis respectivement, on lit
** le fichier, on casse ses instructions bytecode, on traduit ses instructions
** en chaines de caracteres et puis on ecrit un nouveau fichier en .s qui
** correspond au .cor envoye. puis on passe au fichier suivant...
*/

int 		main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 2)
		error(1);
	while (argc > 1)
	{
		data = get_file_info(argv[argc - 1]);
		parse_info(data);
		decompile(data);
		print_file(data);
		free(data);
		data = NULL;
		argc -= 1;
	}
	return (0);
}
