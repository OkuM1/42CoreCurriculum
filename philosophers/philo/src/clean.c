/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:38:58 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 22:12:03 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_up(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosopher_list[i].thread_id, NULL);
		i++;
	}
	destroy_mutexes(sim);
	free_dynamic_memory(sim);
}

void	destroy_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_destroy(&sim->utensils[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->output_lock);
	pthread_mutex_destroy(&sim->meal_lock);
	pthread_mutex_destroy(&sim->is_over_lock);
}

void	free_dynamic_memory(t_simulation *sim)
{
	free(sim->utensils);
	free(sim->philosopher_list);
}
