/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:15:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/26 21:33:11 by mokutucu         ###   ########.fr       */
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

// Structure for a philosopher
typedef struct s_philo
{
    int philo_id;
    long long last_meal_time;
    int number_of_meals;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    struct s_table *table;
}               t_philo;

// Structure for the table
typedef struct s_table
{
    int number_of_philosophers;
    long long time_to_die;  // Changed to long long
    long long time_to_eat;  // Changed to long long
    long long time_to_sleep; // Changed to long long
    int must_eats;
    int philosopher_died;
    t_philo *philo;
}               t_table;

// Function prototypes
long long get_time(void);
int ft_atoi(const char *str);
long long ft_atoll(const char *str);  // Added for long long conversion

#endif
