/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:56:55 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/10 15:26:36 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_color_pixel(int iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	t = ((double)log(iter) / log(MAX_ITER));
	r = 9 * (1 - t) * t * t * t * 255;
	g = 15 * (1 - t) * (1 - t) * t * t * 255;
	b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (r << 16 | g << 8 | b);
}

void	ft_put_pixel(t_vars *vars)
{
	char	*px;

	px = &vars->img.img_addr[vars->coord.win_pos_h * vars->img.line_length
		+ vars->coord.win_pos_w * 4];
	*(unsigned int *)px = ft_color_pixel(vars->coord.iter);
}
