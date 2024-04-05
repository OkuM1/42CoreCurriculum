/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:22:52 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/05 16:35:20 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

static size_t	ft_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

int	get_height(char	*file)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (0);
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close (fd);
	return (height);
}

int	get_width(char *file)
{
	int		fd;
	int		width;
	int		curr_width;
	char	*line;

	width = 0;
	fd = open(file, O_RDONLY);
	if (!fd)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		curr_width = ft_words(line, ' ');
		if (curr_width > width)
			width = curr_width;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close (fd);
	return (width);
}
