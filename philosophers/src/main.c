/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:44:10 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/24 18:07:45 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void init_philo(t_philo *philo)
{
    philo->philo_id = 1;
    philo->time_to_die = 2;
    philo->time_to_eat = 3;
    philo->time_to_sleep = 4;
    philo->number_of_eats = 5;
}

int main(void)
{
    t_philo *philo;
    
    philo = (t_philo *)malloc(sizeof(t_philo));
    init_philo(philo);
    printf("philo_id: %d\n", philo->philo_id);
    return (0);
}