/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:12:57 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 15:58:41 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_philosopher_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosopher_list[i].last_meal_time = get_time();
		if (pthread_create(&sim->philosopher_list[i].thread_id, 
				NULL, philosopher_activity, &sim->philosopher_list[i]))
			return (1);
		i++;
	}
	return (0);
}

int	create_monitor_thread(t_simulation *sim)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, death_monitor, sim))
		return (1);
	pthread_join(monitor_thread, NULL);
	clean_up(sim);
	return (0);
}

int	start_simulation(t_simulation *sim)
{
	sim->start_time = get_time();
	if (create_philosopher_threads(sim))
		return (1);
	return (create_monitor_thread(sim));
}
