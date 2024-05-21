/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:08:44 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/15 15:53:58 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int	close_handler(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->matrix[i]);
		i++;
	}
	free (data->matrix);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free (data->mlx);
	exit(0);
}

int	key_handler(int key, t_data *data)
{
	if (key == 65307)
	{
		ft_printf("%d pressed.\n", key);
		close_handler(data);
	}
	else if (key == 49)
	{
		ft_printf("%d pressed.\n", key);
		data->zoom += 2;
		mlx_clear_window(data->mlx, data->win);
		draw_map(data);
	}
	else if (key == 50)
	{
		data->zoom -= 2;
		mlx_clear_window(data->mlx, data->win);
		draw_map(data);
	}
	else if (key == 52)
	{
		data->angle -= 0.2;
		mlx_clear_window(data->mlx, data->win);
		draw_map(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		return (1);
	}
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	read_map(argv[1], &data);
	data.zoom = 1;
	data.angle = 0.8;
	draw_map(&data);
	mlx_hook(data.win, 17, 0, close_handler, &data);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
