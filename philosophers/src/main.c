/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:05 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/25 23:19:31 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int validate_input(int argc, char **argv)
{
    if (argc != 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    if (ft_atoi(argv[1]) < 1)
    {
        printf("Philosophers must be at least 1\n");
        return (1);   
    }
    return (0);
}

void init_table(t_table *table, t_philo **philo, char **argv)
{
    int i;

    // Zero out the table struct
    memset(table, 0, sizeof(t_table));
    
    // Set table values
    table->number_of_philosophers = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    table->must_eats = ft_atoi(argv[5]);

    // Allocate memory for philosophers
    *philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
    if (!*philo)
    {
        printf("Error: Memory allocation failed for philosophers\n");
        exit(1);
    }
    memset(*philo, 0, sizeof(t_philo) * table->number_of_philosophers);
    table->philo = *philo;

    // Allocate memory for forks (mutexes)
    table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers);
    if (!table->forks)
    {
        printf("Error: Memory allocation failed for forks\n");
        free(*philo);
        exit(1);
    }

    // Initialize forks and assign them to philosophers
    i = 0;
    while (i < table->number_of_philosophers)
    {
        pthread_mutex_init(&table->forks[i], NULL);   // Initialize each fork
        table->philo[i].philo_id = i + 1;
        table->philo[i].left_fork = &table->forks[i];               // Left fork
        table->philo[i].right_fork = &table->forks[(i + 1) % table->number_of_philosophers];  // Right fork (wrap around)
        table->philo[i].time_to_eat = table->time_to_eat;
        table->philo[i].time_to_sleep = table->time_to_sleep;
        table->philo[i].number_of_eats = table->must_eats;
        i++;
    }
}

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        printf("%ld %d is thinking\n", get_time(), philo->philo_id);
        
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken a fork\n", get_time(), philo->philo_id);

        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken a fork\n", get_time(), philo->philo_id);
        printf("%ld %d is eating\n", get_time(), philo->philo_id);
        
        usleep(philo->time_to_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        printf("%ld %d is sleeping\n", get_time(), philo->philo_id);
        usleep(philo->time_to_sleep * 1000);
    }
    return NULL;
}


void create_threads(t_table *table, t_philo *philo)
{
    int i;

    i = 0;
    while (i < table->number_of_philosophers)
    {
        pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
        i++;
    }

    // Join threads to wait for philosophers to finish (they won't in this infinite loop)
    i = 0;
    while (i < table->number_of_philosophers)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_table table;
    t_philo *philo; // Keep as pointer

    if (validate_input(argc, argv))
        return (1);
    
    init_table(&table, &philo, argv); // Pass philo as double pointer
    create_threads(&table, table.philo);

    printf("done\n");

    // Free and clean up
    int i = 0;
    while (i < table.number_of_philosophers)
    {
        pthread_mutex_destroy(&table.forks[i]);  // Destroy fork mutexes
        i++;
    }
    free(table.forks);
    free(table.philo);

    return (0);
}
