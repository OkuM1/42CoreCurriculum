/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:56:24 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 14:34:11 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_key_hook(int keycode, t_vars *vars)
{
	double	delta_x;
	double	delta_y;

	delta_x = vars->coord.x_vmax - vars->coord.x_vmin;
	delta_y = vars->coord.y_vmax - vars->coord.y_vmin;
	if (keycode == ESC)
		ft_exit(vars);
	if (keycode == R)
		ft_reset(vars);
	if (keycode == UP || keycode == LEFT || keycode == DOWN || keycode == RIGHT)
		ft_move_img(keycode, vars, delta_x, delta_y);
	return (0);
}

int	ft_mouse(int keycode, int x, int y, t_vars *vars)
{
	if (keycode == ZOOM_IN)
		ft_zoom(vars, x, y, keycode);
	if (keycode == ZOOM_OUT)
		ft_zoom(vars, x, y, keycode);
	ft_coords(vars);
	mlx_put_image_to_window(vars->img.mlx, vars->img.mlx_win,
		vars->img.img, 0, 0);
	return (0);
}

void	ft_reset(t_vars *vars)
{
	ft_set_limits(vars);
	ft_coords(vars);
	mlx_put_image_to_window(vars->img.mlx, vars->img.mlx_win,
		vars->img.img, 0, 0);
}

int	ft_refresh_image(t_vars *vars)
{
	mlx_put_image_to_window(vars->img.mlx, vars->img.mlx_win,
		vars->img.img, 0, 0);
	return (0);
}
