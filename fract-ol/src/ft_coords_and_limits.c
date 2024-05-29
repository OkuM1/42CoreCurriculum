/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coords_and_limits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:58 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 14:41:12 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_coords(t_vars *vars)
{
	vars->coord.win_pos_h = 0;
	while (vars->coord.win_pos_h < HEIGHT)
	{
		vars->coord.win_pos_w = 0;
		while (vars->coord.win_pos_w < WIDTH)
		{
			ft_viewport(vars);
			vars->ft_calc(vars);
			ft_put_pixel(vars);
			vars->coord.win_pos_w++;
		}
		vars->coord.win_pos_h++;
	}
}

void	ft_set_limits(t_vars *vars)
{
	if (vars->fract.fract_number == 1)
	{
		vars->coord.x_vmax = 1.0;
		vars->coord.x_vmin = -2.0;
		vars->coord.y_vmax = 1.1;
		vars->coord.y_vmin = -1.1;
	}
	else if (vars->fract.fract_number == 2)
	{
		vars->coord.x_vmax = 2.0;
		vars->coord.x_vmin = -2.0;
		vars->coord.y_vmax = 2.0;
		vars->coord.y_vmin = -2.0;
	}
}
