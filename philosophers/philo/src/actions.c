/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:36:45 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 22:53:35 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Function to print the philosopher's action with a timestamp
void	action_print(t_philosopher *philo, const char *str)
{
	long	current_time;

	current_time = get_time() - philo->sim->start_time;
	pthread_mutex_lock(&philo->sim->output_lock);
	pthread_mutex_lock(&philo->sim->is_over_lock);
	if (!philo->sim->is_over)
		printf("%ld %d %s\n", current_time, philo->index, str);
	pthread_mutex_unlock(&philo->sim->is_over_lock);
	pthread_mutex_unlock(&philo->sim->output_lock);
}

void	eat(t_philosopher *philo)
{
	pick_forks(philo, philo->left_fork, philo->right_fork);
	pthread_mutex_lock(&philo->sim->meal_lock);
	action_print(philo, "is eating");
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->sim->meal_lock);
	usleep(philo->sim->eat_time * 1000);
	put_forks(philo, philo->left_fork, philo->right_fork);
}

void	sleep_and_think(t_philosopher *philo)
{
	action_print(philo, "is sleeping");
	usleep(philo->sim->sleep_time * 1000);
	action_print(philo, "is thinking");
	usleep(500);
}

void	*philosopher_routine(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	while (1)
	{
		pthread_mutex_lock(&sim->is_over_lock);
		if (sim->is_over)
		{
			pthread_mutex_unlock(&sim->is_over_lock);
			break ;
		}
		pthread_mutex_unlock(&sim->is_over_lock);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

void	*philosopher_activity(void *params)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)params;
	if (philo->index == 0)
    {
        philo->left_fork = philo->index - 1;
        philo->right_fork = philo->index % philo->sim->num_philosophers;
    }
    else
    {
        philo->left_fork = philo->index % philo->sim->num_philosophers;
        philo->right_fork = philo->index - 1;
    }
	if (philo->sim->num_philosophers == 1)
	{
		action_print(philo, "has taken a fork");
		usleep(philo->sim->die_time * 1000);
		return (NULL);
	}
	if (philo->index % 2 == 0 && philo->sim->num_philosophers > 1)
		usleep(philo->sim->eat_time / 50);
	return (philosopher_routine(philo));
}
