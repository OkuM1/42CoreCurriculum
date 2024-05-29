/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_and_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:57:01 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 13:15:36 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error_msg(void)
{
	printf("\nAvailable Fractals: Mandelbrot, Burning Ship and Julia\n\n");
	printf("Please enter a valid input, follow the example:\n");
	printf("./fractol mandelbrot\n");
	printf("./fractol burning-ship\n\n");
	printf("julia: ./fractol julia 0.40 .355\n");
	exit(0);
}

static int	ft_check_values(char *str, t_parse *parse)
{
	if (*str == '.')
	{
		parse->point++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		parse->nap++;
		str++;
	}
	if ((parse->point > 0 && parse->nap == 0) || (parse->signal > 0
			&& parse->nap == 0) || parse->nbp > 1)
		return (0);
	return ((parse->signal + parse->nbp + parse->point + parse->nap)
		== ft_strlen(parse->tmp));
}

int	ft_check_jvalues(char *str)
{
	t_parse	parse;

	parse.tmp = str;
	parse.signal = 0;
	parse.nbp = 0;
	parse.point = 0;
	parse.nap = 0;
	if (*str == '+' || *str == '-')
	{
		parse.signal++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (*str >= '0' && *str <= '2')
			parse.nbp++;
		str++;
	}
	return (ft_check_values(str, &parse));
}

void	ft_check_args(int argc, char **argv, t_vars *vars)
{
	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		vars->ft_calc = &ft_mandelbrot_calc;
		vars->fract.fract_number = 1;
	}
	else if (argc == 2 && ft_strcmp(argv[1], "burning-ship") == 0)
	{
		vars->ft_calc = &ft_burning_ship;
		vars->fract.fract_number = 2;
	}
	else if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
	{
		if (ft_check_jvalues(argv[2]) && ft_check_jvalues(argv[3]))
		{
			vars->fract.julia_px = ft_atof(argv[2]);
			vars->fract.julia_py = ft_atof(argv[3]);
			vars->ft_calc = &ft_julia_calc;
			vars->fract.fract_number = 2;
		}
		else
			ft_error_msg();
	}
	else
		ft_error_msg();
}
