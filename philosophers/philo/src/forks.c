/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:38:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 22:55:55 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_forks(t_philosopher *philo, int left_fork, int right_fork)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->sim->utensils[left_fork]);
		action_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->sim->utensils[right_fork]);
		action_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->sim->utensils[right_fork]);
		action_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->sim->utensils[left_fork]);
		action_print(philo, "has taken a fork");
	}
}

void	put_forks(t_philosopher *philo, int left_fork, int right_fork)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&philo->sim->utensils[right_fork]);
		pthread_mutex_unlock(&philo->sim->utensils[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->sim->utensils[left_fork]);
		pthread_mutex_unlock(&philo->sim->utensils[right_fork]);
	}
}
