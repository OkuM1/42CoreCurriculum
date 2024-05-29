/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:57:19 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 12:57:21 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_zoom(t_vars *vars, int x, int y, int direction)
{
	double	delta_x;
	double	delta_y;
	double	x_ratio;
	double	y_ratio;

	x_ratio = (double)x / WIDTH;
	y_ratio = (double)y / HEIGHT;
	delta_x = vars->coord.x_vmax - vars->coord.x_vmin;
	delta_y = vars->coord.y_vmax - vars->coord.y_vmin;
	if (direction == ZOOM_IN)
	{
		delta_x = ((1.0 / ZOOM_FACTOR) * delta_x) - delta_x;
		delta_y = ((1.0 / ZOOM_FACTOR) * delta_y) - delta_y;
	}
	else
	{
		delta_x = (ZOOM_FACTOR * delta_x) - delta_x;
		delta_y = (ZOOM_FACTOR * delta_y) - delta_y;
	}
	vars->coord.x_vmin = vars->coord.x_vmin - (delta_x * x_ratio);
	vars->coord.x_vmax = vars->coord.x_vmax + (delta_x * (1 - x_ratio));
	vars->coord.y_vmax = vars->coord.y_vmax + (delta_y * (1 - y_ratio));
	vars->coord.y_vmin = vars->coord.y_vmin - (delta_y * y_ratio);
}

void	ft_move_img(int keycode, t_vars *vars, double delta_x, double delta_y)
{
	if (keycode == UP)
	{
		vars->coord.y_vmax += delta_y * 0.05;
		vars->coord.y_vmin += delta_y * 0.05;
	}
	else if (keycode == LEFT)
	{
		vars->coord.x_vmax += delta_x * 0.05;
		vars->coord.x_vmin += delta_x * 0.05;
	}
	else if (keycode == DOWN)
	{
		vars->coord.y_vmax -= delta_y * 0.05;
		vars->coord.y_vmin -= delta_y * 0.05;
	}
	else
	{
		vars->coord.x_vmax -= delta_x * 0.05;
		vars->coord.x_vmin -= delta_x * 0.05;
	}
	ft_coords(vars);
	mlx_put_image_to_window(vars->img.mlx, vars->img.mlx_win, vars->img.img,
		0, 0);
}
