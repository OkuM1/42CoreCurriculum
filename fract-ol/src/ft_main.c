/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:56:38 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 13:23:57 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_init_render(t_vars	*vars)
{
	vars->img.mlx = mlx_init();
	vars->img.mlx_win = mlx_new_window(vars->img.mlx, WIDTH, HEIGHT, "Fractol");
	vars->img.img = mlx_new_image(vars->img.mlx, WIDTH, HEIGHT);
	vars->img.img_addr = mlx_get_data_addr(vars->img.img, &vars->img.bpp,
			&vars->img.line_length, &vars->img.endian);
	ft_set_limits(vars);
	ft_coords(vars);
	mlx_put_image_to_window(vars->img.mlx, vars->img.mlx_win,
		vars->img.img, 0, 0);
	mlx_key_hook(vars->img.mlx_win, ft_key_hook, vars);
	mlx_mouse_hook(vars->img.mlx_win, ft_mouse, vars);
	mlx_hook(vars->img.mlx_win, 17, 1L << 0, ft_exit, vars);
	mlx_expose_hook(vars->img.mlx_win, ft_refresh_image, vars);
	mlx_loop(vars->img.mlx);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_check_args(argc, argv, &vars);
	ft_init_render(&vars);
}
