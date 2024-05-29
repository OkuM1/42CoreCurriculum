/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:49 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 12:59:54 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_exit(t_vars *vars)
{
	mlx_destroy_image(vars->img.mlx, vars->img.img);
	mlx_clear_window(vars->img.mlx, vars->img.mlx_win);
	mlx_destroy_window(vars->img.mlx, vars->img.mlx_win);
	mlx_destroy_display(vars->img.mlx);
	free(vars->img.mlx);
	exit(0);
}
