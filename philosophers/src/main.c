/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:05 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/26 21:49:52 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int validate_input(int argc, char **argv)
{
    if (argc != 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    if (ft_atoll(argv[1]) < 1)
    {
        printf("Philosophers must be at least 1\n");
        return (1);
    }
    return (0);
}

void init_table(t_table *table, t_philo **philo, char **argv)
{
    memset(table, 0, sizeof(t_table));
    table->number_of_philosophers = ft_atoll(argv[1]);
    table->time_to_die = ft_atoll(argv[2]);
    table->time_to_eat = ft_atoll(argv[3]);
    table->time_to_sleep = ft_atoll(argv[4]);
    table->must_eats = ft_atoll(argv[5]);

    *philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
    if (!*philo)
    {
        printf("Error: Memory allocation failed for philosophers\n");
        exit(1);
    }
    memset(*philo, 0, sizeof(t_philo) * table->number_of_philosophers);

    table->philo = *philo;
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    while (1)
    {
        if (table->philosopher_died)
            return (NULL);

        printf("Philosopher %d is thinking\n", philo->philo_id);
        usleep(1000 * table->time_to_sleep);

        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);

        philo->last_meal_time = get_time();
        philo->number_of_meals++;
        printf("Philosopher %d is eating\n", philo->philo_id);
        usleep(1000 * table->time_to_eat);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        printf("Philosopher %d is sleeping\n", philo->philo_id);
        usleep(1000 * table->time_to_sleep);
    }

    return (NULL);
}

void create_threads(t_table *table, t_philo *philo)
{
    int i = 0;
    pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers);

    while (i < table->number_of_philosophers)
    {
        pthread_mutex_init(&forks[i], NULL);
        philo[i].philo_id = i + 1;
        philo[i].table = table;
        philo[i].left_fork = &forks[i];
        philo[i].right_fork = &forks[(i + 1) % table->number_of_philosophers];
        pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_table table;
    t_philo *philo;

    if (validate_input(argc, argv))
        return (1);

    init_table(&table, &philo, argv);
    create_threads(&table, table.philo);

    printf("Philosophers simulation is running...\n");

    // Join all threads (optional)
    int i = 0;
    while (i < table.number_of_philosophers)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }

    free(table.philo);
    return (0);
}
