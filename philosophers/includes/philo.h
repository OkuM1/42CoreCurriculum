/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:15:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/03 16:51:02 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// Philosopher structure
typedef struct s_philosopher {
    int index;
    int meal_count;
    long last_meal_time;
    pthread_t thread_id;
    struct s_simulation *sim;
    int left_fork;
    int right_fork;
} t_philosopher;

// Environment structure for managing philosophers
typedef struct s_simulation {
    int num_philosophers;
    int die_time;
    int eat_time;
    int sleep_time;
    int max_eat_count;
    pthread_mutex_t *utensils;
    pthread_mutex_t output_lock;
    pthread_mutex_t meal_lock;
    long start_time;
    int is_over;
    int all_fed;
    t_philosopher *philosopher_list;
} t_simulation;

// Function prototypes
int main(int argc, char *argv[]);
int validate_input(t_simulation *sim, int argc, char *argv[]);
int initialize_utensils(t_simulation *sim);
int allocate_resources(t_simulation *sim);
void *philosopher_activity(void *params);
int start_simulation(t_simulation *sim);
void clean_up(t_simulation *sim);
void *death_monitor(void *params);
long get_time(); // Assumed to be defined elsewhere
void new_sleep(int duration); // Assumed to be defined elsewhere
int ft_isnumber(const char *str); // Assumed to be defined elsewhere
int ft_atoi(const char *str); // Assumed to be defined elsewhere

#endif // PHILOSOPHERS_H