/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:04:54 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/05 16:35:18 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int	map_elevation_to_color(int elevation)
{
	if (elevation > 10)
		return (0xFF0000);
	else if (elevation > 5)
		return (0x00FF00);
	else if (elevation > 1)
		return (0x0000FF);
	else if (elevation > 0)
		return (0xFFFF00);
	else
		return (0xFFFFFF);
}

void	isometric(t_data *data)
{
	float	x0_temp;
	float	x1_temp;

	x1_temp = (data->x1 - data->y1);
	x0_temp = (data->x0 - data->y0);
	data->x0 = x0_temp * cos(data->angle);
	data->y0 = (x0_temp + data->y0) * sin(data->angle) - data->elev0;
	data->x1 = x1_temp * cos(data->angle);
	data->y1 = (x1_temp + data->y1) * sin(data->angle) - data->elev1;
}

void	update_coordinates(t_data *data)
{
	data->x0 = data->x0 - data->width / 2.0 + WINDOW_WIDTH / 2.0;
	data->x1 = data->x1 - data->width / 2.0 + WINDOW_WIDTH / 2.0;
	data->y0 = data->y0 - data->height / 2.0 + WINDOW_HEIGHT / 2.0;
	data->y1 = data->y1 - data->height / 2.0 + WINDOW_HEIGHT / 2.0;
}

void	zoom_multiply(t_data *data)
{
	data->x0 *= data->zoom;
	data->y0 *= data->zoom;
	data->x1 *= data->zoom;
	data->y1 *= data->zoom;
}

void	calculate_differences(t_data *data)
{
	data->dx = fabs(data->x1 - data->x0);
	data->dy = fabs(data->y1 - data->y0);
	if (data->dx > data->dy)
	{
		data->max = data->dx;
	}
	else
	{
		data->max = data->dy;
	}
	data->dx = (data->x1 - data->x0) / data->max;
	data->dy = (data->y1 - data->y0) / data->max;
}
