/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_burning_ship.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:55:43 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 12:55:45 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_burning_ship(t_vars *vars)
{
	t_coord	*coord;

	coord = &vars->coord;
	coord->zx = 0;
	coord->zy = 0;
	coord->xx = 0;
	coord->yy = 0;
	coord->temp = 0;
	coord->iter = 0;
	while (coord->xx + coord->yy < 4 && coord->iter < MAX_ITER)
	{
		coord->zx = coord->xx - coord->yy + coord->x_viewp;
		coord->zy = fabs(coord->temp - coord->xx - coord->yy) + coord->y_viewp;
		coord->xx = coord->zx * coord->zx;
		coord->yy = coord->zy * coord->zy;
		coord->temp = (coord->zx + coord->zy) * (coord->zx + coord->zy);
		coord->iter++;
	}
}
