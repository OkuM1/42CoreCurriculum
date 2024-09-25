/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:15:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/25 23:19:29 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>


typedef struct s_philo
{
    int             philo_id;         // Philosopher ID
    int             number_of_eats;   // Number of times the philosopher has eaten
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    pthread_t       thread;
    pthread_mutex_t *left_fork;       // Pointer to the left fork (mutex)
    pthread_mutex_t *right_fork;      // Pointer to the right fork (mutex)
}               t_philo;

typedef struct s_table
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eats;
    t_philo         *philo;           // Array of philosophers
    pthread_mutex_t *forks;           // Array of fork mutexes
}               t_table;

int     ft_atoi(const char *str);
void    init_table(t_table *table, t_philo **philo, char **argv);
void    create_threads(t_table *table, t_philo *philo);

#endif
