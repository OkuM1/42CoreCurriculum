/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:10:18 by mokutucu          #+#    #+#             */
/*   Updated: 2024/03/11 20:26:57 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	send_message(int pid, char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i] != '\0')
	{
		count = 0;
		while (count <= 7)
		{
			if (str[i] & (1 << count))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			count++;
			usleep(100);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		ft_printf("Please enter PID and message only.");
	}
	else
	{
		pid = ft_atoi(av[1]);
		if (pid < 0)
			return (1);
		send_message(pid, av[2]);
		return (1);
	}
	return (0);
}
