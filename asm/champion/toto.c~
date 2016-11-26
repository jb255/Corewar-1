#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft/includes/libft.h"

unsigned char		calc_octet(unsigned int *nbr, unsigned int diviseur)
{
	int a;
	int b;
	unsigned char total;

	a = 128;
	b = 8;
	total = 0;
	while (b > 0)
	{
		printf("%u %u\n", *nbr, diviseur);
		total += ((*nbr / diviseur) * a);
		*nbr %= diviseur;
		diviseur /= 2;
		a /= 2;
		b --;
	}
	return (total);
}

unsigned char		*cut_nbr(unsigned nbr) // cree un tab de 4 char   
{
	unsigned char *tab;

	tab = (unsigned char *)ft_memalloc(sizeof (unsigned char) * 5);
	if (!tab)
		printf("malloc error\n");
	tab[0] = calc_octet(&nbr, 2147483648);
	tab[1] = calc_octet(&nbr, 8388608);
	tab[2] = calc_octet(&nbr, 32768);
	tab[3] = calc_octet(&nbr, 128);
	return (tab);
}

unsigned int	little_to_big(unsigned int little)
{
	unsigned int	big;

	big = ((little >> 24 ) & 0xff) | ((little << 8) & 0xff0000) |
	((little >> 8) & 0xff00) | ((little << 24 )& 0xff000000);
	return (big);
}

int		main(void)
{
	int			fd;

	if ((fd = open("toto.cor", O_WRONLY, 0644)) == -1)
		printf(" error open\n");

	int b = 3401123;
	unsigned char* a;
	a = cut_nbr(3401123);
	write (fd, &b, 4);
	printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
	write (fd, &a[0], 1);
	write (fd, &a[1], 1);
	write (fd, &a[2], 1);
	write (fd, &a[3], 1);
	write (fd, &a[4], 1);

	unsigned int	toto;
	toto = 3401123;
	toto = little_to_big(3401123);
	write(fd, &toto, 4);

	if (close(fd) != 0)
		printf("close_error_.cor");
}
