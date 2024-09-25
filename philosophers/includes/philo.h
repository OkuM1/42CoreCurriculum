/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:15:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/25 21:04:59 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

// Struct for each individual philosopher
typedef struct s_philo
{
    int philo_id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_eats;
    pthread_t thread;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
}              t_philo;

// Struct for main thread aka. the table
typedef struct s_table
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eats;
    t_philo *philo;
}              t_table;

int	ft_atoi(const char *str);

# endif