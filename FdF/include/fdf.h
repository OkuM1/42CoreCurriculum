/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:55:41 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/05 16:35:16 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/mlxlib/mlx.h"
# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		**matrix;
	int		width;
	int		height;
	float	zoom;
	int		color0;
	int		color1;
	float	x0;
	float	y0;
	float	x1;
	float	y1;
	int		elev0;
	int		elev1;
	float	dx;
	float	dy;
	float	max;
	float	angle;
}	t_data;

void	draw_horizontal_lines(t_data *data, int x, int y);
void	draw_vertical_lines(t_data *data, int x, int y);
void	draw_map(t_data *data);
void	draw_lines(t_data *data);
void	zoom_multiply(t_data *data);
void	isometric(t_data *data);
int		map_elevation_to_color(int elevation);
void	read_map(char *file, t_data *data);
int		max(int a, int b);
int		get_height(char	*file);
int		get_width(char *file);

#endif
