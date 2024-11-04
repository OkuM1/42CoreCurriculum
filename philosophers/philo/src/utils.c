/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:54:30 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 20:02:32 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Convert a string to an integer
int	ft_isnumber(const char *str)
{
	int	i;

	if (!str || *str == '\0') 
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+') 
		i++;
	while (str[i]) 
	{
		if (str[i] < '0' || str[i] > '9') 
			return (0);
		i++;
	}
	return (1);
}

// Get the current time in milliseconds
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
