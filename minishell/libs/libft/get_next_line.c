/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:59:50 by mokutucu          #+#    #+#             */
/*   Updated: 2024/03/11 15:09:09 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_linesbuffer(int fd, char *save, char *buffer);
static char	*fixline(char *line);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(save);
		free(buffer);
		save = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = fill_linesbuffer(fd, save, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	save = fixline(line);
	return (line);
}

static char	*fixline(char *line_buffer)
{
	char	*save;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0)
		return (NULL);
	save = gft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*save == 0)
	{
		free(save);
		save = NULL;
	}
	line_buffer[i + 1] = 0;
	return (save);
}

static char	*fill_linesbuffer(int fd, char *save, char *buffer)
{
	ssize_t	readstatus;
	char	*tmp;

	readstatus = 1;
	while (readstatus > 0)
	{
		readstatus = read(fd, buffer, BUFFER_SIZE);
		if (readstatus == -1)
			return (NULL);
		else if (readstatus == 0)
			break ;
		buffer[readstatus] = '\0';
		if (!save)
		{
			save = gft_strdup("");
		}
		tmp = save;
		save = gft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (gft_strchr(buffer, '\n'))
			break ;
	}
	return (save);
}

// int main() {
//     char file[] = "text.txt";
// 	int fd;
//     char *line;

//     fd = open(file, O_RDONLY);
//     if (fd == -1) {
//         return 1;
//     }

//     // Read lines from the file using get_next_line
//     //while (( != NULL) {
// 		line = get_next_line(fd);
//         printf("Line: %s\n", line);
// 		line = get_next_line(fd);
//         printf("Line: %s\n", line);
//         //free(line); // Free the memory allocated by get_next_line

//     close(fd); // Close the file descriptor
//     return 0;
// }
