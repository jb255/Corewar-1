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

 // Error codes :
 // 1. No file given
 // 2. Could not open file
 // 3. Error reading file
 // 4. Error allocating memory

void		error(char *s1, char *s2)
{
	write(1, "\033[:31m", 6);
	write(1, s1, ft_strlen(s1));
	write(1, s2, ft_strlen(s2));
	write(1, "\n", 1);
	write(1, "\033[:0m", 6);

}

void		ft_header_and_create(char *file_name, int *fd_w, int *fd_r)
{
	char	*tmp;
	char	*beg;

	beg = file_name;
	*fd_r = open(file_name, O_RDONLY);
	if (*fd_r == -1)
		error("Could not open file : ", file_name);
	tmp = file_name + ft_strlen(file_name);
	while (*tmp != '/' && tmp != file_name)
		tmp--;
	file_name += ft_strlen(file_name) - 3;
	file_name[0] = 's';
	file_name[1] = 0;
	file_name = tmp + 1;
	*fd_w = open(file_name, O_CREAT | S_IRWXU | S_IWUSR);
	if (*fd_w == -1)
		error("Could not create file : ", file_name);
	free(beg);
	read(*fd_r, tmp, sizeof(header_t));
	printf("tmp : %s\n", tmp);
	write(*fd_w, ".name\t\t", 7);
	while (*tmp != 0)
		write(*fd_w, tmp++, 1);
	write(*fd_w, "\n", 1);
	while (*tmp == 0)
		tmp++;
	write(*fd_w, ".comment\t\t", 10);
	while (*tmp != 0)
		write(*fd_w, tmp++, 1);
	write(*fd_w, "\n", 1);
}

void		ft_parse(char *tmp, int fd_w, int fd_r)
{
	return;
}

int 		main(int argc, char **argv)
{
	char	*tmp;
	int		fd_w;
	int		fd_r;

	if (argc < 2)
		error("Too few arguments passed to the '__main__' function", "");
	while (argc > 1)
	{
		tmp = ft_strdup(argv[argc - 1]);
		ft_header_and_create(tmp, &fd_w, &fd_r);
		ft_parse(tmp, fd_w, fd_r);
		argc -= 1;
	}
	return (0);
}
