/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:10:04 by mokutucu          #+#    #+#             */
/*   Updated: 2024/03/11 20:18:05 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int signal)
{
	static int						i = 0;
	static unsigned char			letter = 0;

	if (signal == SIGUSR1)
	{
		letter |= (1 << i);
	}
	else
	{
		letter |= (0 << i);
	}
	i++;
	if (i == 8)
	{
		ft_putchar_fd(letter, 1);
		i = 0;
		letter = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
}
