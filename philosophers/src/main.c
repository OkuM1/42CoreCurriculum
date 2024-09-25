/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:05 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/25 21:57:13 by mokutucu         ###   ########.fr       */
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
    // Zero out the table struct
    memset(table, 0, sizeof(t_table)); 
    table->number_of_philosophers = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    table->must_eats = ft_atoi(argv[5]);

    // Allocate memory for philosophers and zero it out
    *philo = malloc(sizeof(t_philo) * table->number_of_philosophers); 
    if (!*philo)
    {
        printf("Error: Memory allocation failed for philosophers\n");
        exit(1);
    }
    
    // Zero out the philosophers array
    memset(*philo, 0, sizeof(t_philo) * table->number_of_philosophers);
    
    // Assign the pointer to the table struct
    table->philo = *philo;
}

pthread_mutex_t print_mutex;

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    pthread_mutex_lock(&print_mutex);
    printf("Philosopher %d is thinking\n", philo->philo_id);
    pthread_mutex_unlock(&print_mutex);

    usleep(philo->time_to_eat * 1000); // Simulate thinking and eating

    pthread_mutex_lock(&print_mutex);
    printf("Philosopher %d is eating\n", philo->philo_id);
    pthread_mutex_unlock(&print_mutex);

    usleep(philo->time_to_sleep * 1000); // Simulate sleeping

    return NULL;
}

void create_threads(t_table *table, t_philo *philo)
{
    int i;

    i = 0;
    while (i < table->number_of_philosophers)
    {
        philo[i].philo_id = i + 1;
        philo[i].time_to_die = table->time_to_die;
        philo[i].time_to_eat = table->time_to_eat;
        philo[i].time_to_sleep = table->time_to_sleep;
        philo[i].number_of_eats = table->must_eats;
        pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
        i++;
    }

    // Wait for all threads to finish
    i = 0;
    while (i < table->number_of_philosophers)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}

// argv: [number of philosophers, time to die, time to eat, time to sleep, number of eats]
int main(int argc, char **argv)
{
    t_table table;
    t_philo *philo;
    
    if (validate_input(argc, argv))
        return (1);
    
    init_table(&table, &philo, argv);
    
    pthread_mutex_init(&print_mutex, NULL);
    create_threads(&table, table.philo);

    printf("All philosophers have finished.\n");
    pthread_mutex_destroy(&print_mutex); // Destroy mutex

    free(table.philo);
    return (0);
}
