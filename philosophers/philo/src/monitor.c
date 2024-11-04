/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:39:59 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 23:00:12 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_monitor(void *params)
{
	t_simulation	*sim;
	long long		time_to_die;

	sim = (t_simulation *)params;
	time_to_die = sim->die_time;
	while (!sim->is_over)
	{
		check_for_death(sim, time_to_die);
		usleep(1000);
	}
	return (NULL);
}

void	check_for_death(t_simulation *sim, long long time_to_die)
{
	int			i;
	int			all_fed;

	all_fed = 0;
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_lock(&sim->meal_lock);
		if (get_time() - 
			sim->philosopher_list[i].last_meal_time > time_to_die)
		{
			pthread_mutex_unlock(&sim->meal_lock);
			announce_death(sim, i, get_time());
			return ;
		}
		if (sim->max_eat_count > 0 
			&& sim->philosopher_list[i].meal_count >= sim->max_eat_count)
			all_fed++;
		pthread_mutex_unlock(&sim->meal_lock);
		i++;
	}
	pthread_mutex_lock(&sim->is_over_lock);
	if (all_fed == sim->num_philosophers)
		sim->is_over = 1;
	pthread_mutex_unlock(&sim->is_over_lock);
}

void	announce_death(t_simulation *sim, int index, long current_time)
{
	pthread_mutex_lock(&sim->output_lock);
	printf("%ld %d died\n", current_time - sim->start_time, 
		sim->philosopher_list[index].index);
	pthread_mutex_lock(&sim->is_over_lock);
	sim->is_over = 1;
	pthread_mutex_unlock(&sim->is_over_lock);
	pthread_mutex_unlock(&sim->output_lock);
}
