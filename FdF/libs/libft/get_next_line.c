/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:59:50 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/02 14:22:10 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_buffer(char *stach, char *buffer)
{
	char	*tmp;

	tmp = gft_strjoin(stach, buffer);
	free(stach);
	return (tmp);
}

char	*fill_stach(int fd, char *stach)
{
	char	*buffer;
	int		bytes_read;

	if (!stach)
		stach = gft_calloc(1, 1);
	buffer = gft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stach);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stach = join_buffer(stach, buffer);
		if (gft_strchr(stach, '\n') != NULL)
			break ;
	}
	free(buffer);
	return (stach);
}

char	*get_tail(char *stach)
{
	char	*next_stach;
	int		i;
	int		j;

	i = 0;
	while (stach[i] && stach[i] != '\n')
		i++;
	if (!stach[i])
	{
		free(stach);
		return (NULL);
	}
	next_stach = gft_calloc(gft_strlen(stach) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (stach[i])
		next_stach[j++] = stach[i++];
	free(stach);
	return (next_stach);
}

char	*fill_line(char *stach)
{
	char	*line;
	int		i;

	i = 0;
	if (!stach[i])
		return (NULL);
	while (stach[i] && stach[i] != '\n')
		i++;
	line = gft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stach[i] && stach[i] != '\n')
	{
		line[i] = stach[i];
		i++;
	}
	if (stach[i] && stach[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stach;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	stach = fill_stach(fd, stach);
	if (!stach)
		return (NULL);
	next_line = fill_line(stach);
	stach = get_tail(stach);
	return (next_line);
}
