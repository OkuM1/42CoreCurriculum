/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:45:35 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/05 16:29:17 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

// Function to fill a row of the matrix with integers
void	fill_matrix(int *row, char *line)
{
	char	**nums;
	int		i;

	nums = ft_split(line, ' ');
	i = 0;
	while (nums[i])
	{
		row[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	init_map_size(char *file, t_data *data)
{
	data->height = get_height(file);
	data->width = get_width(file);
}

void	read_map(char *file, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	init_map_size(file, data);
	fd = open(file, O_RDONLY);
	if (!fd)
		return ;
	data->matrix = (int **)ft_calloc((data->height), sizeof(int *));
	if (!data->matrix)
		return ;
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->matrix[i] = (int *)ft_calloc((data->width), sizeof(int));
		if (!data->matrix[i])
			return ;
		fill_matrix(data->matrix[i], line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	printf("Map loaded into matrix.");
	close(fd);
}
