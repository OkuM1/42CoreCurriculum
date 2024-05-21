/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:39:22 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/15 15:54:01 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	update_coordinates(t_data *data);
void	calculate_differences(t_data *data);

//check if diff is 0 which means false. if not, draw pixels
void	draw_pixels(t_data *data)
{
	int	iterations;
	int	i;

	iterations = max(abs((int)(data->x1 - data->x0)),
			abs((int)(data->y1 - data->y0)));
	i = 0;
	while (i <= iterations)
	{
		mlx_pixel_put(data->mlx, data->win, data->x0, data->y0, data->color0);
		data->x0 += data->dx;
		data->y0 += data->dy;
		i++;
	}
}

void	draw_lines(t_data *data)
{
	data->elev0 = data->matrix[(int)data->y0][(int)data->x0];
	data->elev1 = data->matrix[(int)data->y1][(int)data->x1];
	zoom_multiply(data);
	data->color0 = map_elevation_to_color(data->elev0);
	data->color1 = map_elevation_to_color(data->elev1);
	isometric(data);
	update_coordinates(data);
	calculate_differences(data);
	draw_pixels(data);
}

void	draw_horizontal_lines(t_data *data, int x, int y)
{
	if (x < data->width - 1)
	{
		data->x0 = x;
		data->y0 = y;
		data->x1 = x + 1;
		data->y1 = y;
		draw_lines(data);
	}
}

void	draw_vertical_lines(t_data *data, int x, int y)
{
	if (y < data->height - 1)
	{
		data->x0 = x;
		data->y0 = y;
		data->x1 = x;
		data->y1 = y + 1;
		draw_lines(data);
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			draw_horizontal_lines(data, x, y);
			draw_vertical_lines(data, x, y);
			x++;
		}
		y++;
	}
}
