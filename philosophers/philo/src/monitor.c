/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:39:59 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 21:12:46 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_monitor(void *params)
{
	t_simulation	*sim;
	long			time_to_die;

	sim = (t_simulation *)params;
	time_to_die = sim->die_time;
	while (!sim->is_over)
	{
		check_for_death(sim, time_to_die);
		usleep(1000);
	}
	return (NULL);
}

void	check_for_death(t_simulation *sim, long time_to_die)
{
	long	current_time;
	int		i;
	int		all_fed;

	all_fed = 0;
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_lock(&sim->meal_lock);
		current_time = get_time();
		if (current_time - sim->philosopher_list[i].last_meal_time > time_to_die)
		{
			pthread_mutex_unlock(&sim->meal_lock);
			announce_death(sim, i, current_time);
		}
		if (sim->max_eat_count > 0 
			&& sim->philosopher_list[i].meal_count >= sim->max_eat_count)
			all_fed++;
		pthread_mutex_unlock(&sim->meal_lock);
		i++;
	}

	if (all_fed == sim->num_philosophers)
	{
		sim->is_over = 1;
	}
}

void	announce_death(t_simulation *sim, int index, long current_time)
{
	pthread_mutex_lock(&sim->output_lock);
	printf("%ld %d died\n", current_time - sim->start_time, 
		sim->philosopher_list[index].index);
	sim->is_over = 1;
	pthread_mutex_unlock(&sim->output_lock);
}
