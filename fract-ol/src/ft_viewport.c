/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viewport.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:57:13 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 14:40:11 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_viewport(t_vars *vars)
{
	vars->coord.sf_x = (double)(vars->coord.x_vmax - vars->coord.x_vmin)
		/ WIDTH;
	vars->coord.sf_y = (double)(vars->coord.y_vmax - vars->coord.y_vmin)
		/ HEIGHT;
	vars->coord.x_viewp = vars->coord.x_vmin + (double)((vars->coord.win_pos_w)
			* vars->coord.sf_x);
	vars->coord.y_viewp = vars->coord.y_vmin + (double)((vars->coord.win_pos_h)
			* vars->coord.sf_y);
}
