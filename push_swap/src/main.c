/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:03:01 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/22 18:58:11 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	input_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (str[i] == '-' && ft_isdigit(str[i + 1]))
			i++;
		if (!ft_isdigit(str[i]))
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	input_check(av[1]);
}
