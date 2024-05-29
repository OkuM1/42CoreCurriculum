/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:02:03 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 14:41:00 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define ZOOM_FACTOR 1.05
# define MAX_ITER 128
# define ZOOM_OUT 5
# define ZOOM_IN 4
# define ESC 65307
# define R 114
# define C 67
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363

typedef struct s_img
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_coord
{
	double	x_viewp;
	double	y_viewp;
	double	sf_x;
	double	sf_y;
	double	x_vmax;
	double	x_vmin;
	double	y_vmax;
	double	y_vmin;
	double	zx;
	double	zy;
	double	xx;
	double	yy;
	double	temp;
	int		win_pos_h;
	int		win_pos_w;
	int		iter;
}	t_coord;

typedef struct s_fract
{
	double	julia_px;
	double	julia_py;
	int		fract_number;
}	t_fract;

typedef struct s_parse
{
	size_t	signal;
	size_t	nbp;
	size_t	point;
	size_t	nap;
	char	*tmp;
}	t_parse;

typedef struct s_vars
{
	void	(*ft_calc)(struct s_vars *);
	int		color_shift;
	t_img	img;
	t_coord	coord;
	t_fract	fract;
}	t_vars;

void	ft_init_render(t_vars *vars);
void	ft_viewport(t_vars *vars);
void	ft_put_pixel(t_vars *vars);
void	ft_set_limits(t_vars *vars);
void	ft_coords(t_vars *vars);
void	ft_zoom(t_vars *vars, int x, int y, int direction);
void	ft_julia_calc(t_vars *vars);
void	ft_mandelbrot_calc(t_vars *vars);
void	ft_burning_ship(t_vars *vars);
void	ft_reset(t_vars *vars);
void	ft_color_shift(t_vars *vars);
void	ft_check_args(int argc, char **argv, t_vars *vars);
void	ft_move_img(int keycode, t_vars *vars, double delta_x, double delta_y);
int		ft_check_jvalues(char *str);
int		ft_key_hook(int keycode, t_vars *vars);
int		ft_mouse(int keycode, int x, int y, t_vars *vars);
int		ft_refresh_image(t_vars *vars);
int		ft_exit(t_vars *vars);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(int c);
size_t	ft_strlen(const char *str);
double	ft_atof(char *nptr);

#endif
