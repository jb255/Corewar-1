/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:00:57 by vlancien          #+#    #+#             */
/*   Updated: 2016/05/05 18:49:39 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int		nb_word;

	nb_word = 0;
	while (*s && *s == c)
		++s;
	while (*s)
	{
		while (*s && *s != c)
			++s;
		++nb_word;
		while (*s && *s == c)
			++s;
	}
	return (nb_word);
}

static int	count_letters(char **index, char c)
{
	int		nb_letter;

	nb_letter = 0;
	while (**index == c)
		++*index;
	while (**index != c && **index)
	{
		++nb_letter;
		++*index;
	}
	return (nb_letter);
}

static void	put_letters(char *str, char *word, char c)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] == c)
		++i;
	j = 0;
	while (str[i] != c && str[i])
	{
		word[j] = str[i];
		++i;
		++j;
	}
	word[j] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	int		nb_word;
	char	**tab;
	char	*index;
	char	*tmp;
	int		i;

	if (!s)
		return (NULL);
	nb_word = count_word(s, c);
	if ((tab = (char **)malloc(sizeof(*tab) * (nb_word + 1))) == NULL)
		return (NULL);
	tab[nb_word] = NULL;
	index = (char *)s;
	i = -1;
	while (++i < nb_word)
	{
		tmp = index;
		if ((tab[i] = (char *)malloc(count_letters(&index, c) + 1)) == NULL)
			return (NULL);
		put_letters(tmp, tab[i], c);
	}
	return (tab);
}
