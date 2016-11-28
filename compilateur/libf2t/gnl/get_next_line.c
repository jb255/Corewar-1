/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlancien <vlancien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 20:15:20 by vlancien          #+#    #+#             */
/*   Updated: 2016/05/29 00:54:27 by vlancien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy_line(char **line, char *buf)
{
	int		i[2];
	char	*temp;

	ft_memset(i, 0, sizeof(i));
	if (*line)
	{
		temp = ft_strdup(*line);
		free(*line);
		i[0] = ft_strlen(temp) + ft_strlen(buf) + 1;
		*line = (char *)malloc(sizeof(char) * (i[0]));
		ft_strcpy(*line, temp);
		free(temp);
		while ((*line)[i[1]])
			i[1]++;
	}
	else
	{
		i[0] = ft_strlen(buf) + 1;
		*line = (char *)malloc(sizeof(char) * (i[0]));
	}
	while (*buf != '\0' && *buf != '\n')
		(*line)[i[1]++] = *buf++;
	(*line)[i[1]] = '\0';
}

static char	*ft_sort_string(char *buf)
{
	while (*buf != '\n' && *buf != '\0')
		buf++;
	if (buf[0] == '\n' && buf[1] != '\0')
		return (ft_strdup(++buf));
	return (NULL);
}

static int	ft_check_string(char **line, char **tab)
{
	char	*free_me;

	if (*tab && ft_strchr(*tab, '\n'))
	{
		ft_copy_line(line, *tab);
		free_me = *tab;
		*tab = ft_sort_string(free_me);
		free(free_me);
		return (1);
	}
	if (*tab && !ft_strchr(*tab, '\n'))
	{
		*line = ft_strdup(*tab);
		free(*tab);
		*tab = NULL;
	}
	return (0);
}

static int	ft_error_init(int const fd, char **line, char **string, char **buf)
{
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (line)
		*line = NULL;
	if (ft_check_string(line, string))
		return (1);
	*buf = ft_strnew(BUFF_SIZE);
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static char	*tab = NULL;
	int			valid_fd;
	char		*buf;

	if ((valid_fd = ft_error_init(fd, line, &tab, &buf)) != 0)
		return (valid_fd);
	while ((valid_fd = read(fd, buf, BUFF_SIZE)) > 0 && !ft_strchr(buf, '\n'))
	{
		ft_copy_line(line, buf);
		ft_memset(buf, '\0', BUFF_SIZE);
	}
	if (valid_fd > 0)
	{
		buf[valid_fd] = '\0';
		ft_copy_line(line, buf);
		tab = ft_sort_string(buf);
	}
	free(buf);
	if ((valid_fd > 0) || (valid_fd == 0 && *line != NULL))
		return (1);
	return (valid_fd);
}
