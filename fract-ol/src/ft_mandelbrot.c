/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:56:48 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 12:56:50 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_mandelbrot_calc(t_vars *vars)
{
	vars->coord.zx = 0;
	vars->coord.zy = 0;
	vars->coord.xx = 0;
	vars->coord.yy = 0;
	vars->coord.temp = 0;
	vars->coord.iter = 0;
	while (vars->coord.xx + vars->coord.yy < 4 && vars->coord.iter < MAX_ITER)
	{
		vars->coord.zx = vars->coord.xx - vars->coord.yy + vars->coord.x_viewp;
		vars->coord.zy = (vars->coord.temp - vars->coord.xx - vars->coord.yy)
			+ vars->coord.y_viewp;
		vars->coord.xx = vars->coord.zx * vars->coord.zx;
		vars->coord.yy = vars->coord.zy * vars->coord.zy;
		vars->coord.temp = (vars->coord.zx + vars->coord.zy) * (vars->coord.zx
				+ vars->coord.zy);
		vars->coord.iter++;
	}
}
