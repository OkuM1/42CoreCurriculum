/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:12:57 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/03 23:49:06 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Function to print the philosopher's action with a timestamp
void action_print(t_philosopher *philo, const char *str) 
{
    long current_time = get_time() - philo->sim->start_time; // Calculate elapsed time
    pthread_mutex_lock(&philo->sim->output_lock); // Lock before printing
    if (!philo->sim->is_over) // Only print if the simulation is still active
        printf("%ld %d %s\n", current_time, philo->index, str);
    pthread_mutex_unlock(&philo->sim->output_lock); // Unlock after printing
}

void pick_forks(t_philosopher *philo, int left_fork, int right_fork)
{
    pthread_mutex_lock(&philo->sim->utensils[left_fork]);
    pthread_mutex_lock(&philo->sim->utensils[right_fork]);
}

void put_forks(t_philosopher *philo, int left_fork, int right_fork)
{
    pthread_mutex_unlock(&philo->sim->utensils[left_fork]);
    pthread_mutex_unlock(&philo->sim->utensils[right_fork]);
}

void eat(t_philosopher *philo)
{
    pick_forks(philo, philo->left_fork, philo->right_fork);
    pthread_mutex_lock(&philo->sim->meal_lock);
    action_print(philo, "is eating");
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->sim->meal_lock);
    philo->meal_count++;
    usleep(philo->sim->eat_time * 1000);
    put_forks(philo, philo->left_fork, philo->right_fork);
}

void sleep_and_think(t_philosopher *philo)
{
    action_print(philo, "is sleeping");
    usleep(philo->sim->sleep_time * 1000);
    action_print(philo, "is thinking");
    usleep(philo->sim->sleep_time * 1000);
}

void *philosopher_activity(void *params) {
    t_philosopher *philo = (t_philosopher *)params;
    t_simulation *sim = philo->sim;
    philo->left_fork = philo->index - 1;
    philo->right_fork = philo->index % sim->num_philosophers;

    // Alternate sleeping to avoid starvation
    if (philo->index % 2 == 0 && sim->num_philosophers > 1) 
        usleep(sim->eat_time / 50); // Short sleep to stagger eating

    while (1) {
        eat(philo);
        sleep_and_think(philo);

        pthread_mutex_lock(&sim->meal_lock);
        if (sim->is_over || (sim->max_eat_count != -1 && philo->meal_count >= sim->max_eat_count)) {
            pthread_mutex_unlock(&sim->meal_lock);
            break;
        }
        pthread_mutex_unlock(&sim->meal_lock);
    }
    return NULL;
}


void *death_monitor(void *params)
{
    t_simulation *sim = (t_simulation *)params;
    long time_to_die = sim->die_time;

    while (!sim->is_over)
    {
        if (check_for_death(sim, time_to_die))
            break; // If a philosopher dies, exit the loop
        usleep(1000); // Check every millisecond
    }
    return NULL;
}


int check_for_death(t_simulation *sim, long time_to_die)
{
    long current_time;
    int i;
    
    i = 0;
    while (i < sim->num_philosophers && !sim->is_over)
    {
        current_time = get_time();
        pthread_mutex_lock(&sim->meal_lock);
        if ((int)current_time - sim->philosopher_list[i].last_meal_time > time_to_die)
        {
            announce_death(sim, i, current_time);
            pthread_mutex_unlock(&sim->meal_lock);
            return 1;
        }
        pthread_mutex_unlock(&sim->meal_lock);
        i++;
    }
    return 0;
}

void announce_death(t_simulation *sim, int index, long current_time)
{
    pthread_mutex_lock(&sim->output_lock);
    printf("%ld %d died\n", current_time - sim->start_time, sim->philosopher_list[index].index);
    sim->is_over = 1;
    pthread_mutex_unlock(&sim->output_lock);
}

void clean_up(t_simulation *sim)
{
    int i = 0;
    while (i < sim->num_philosophers)
    {
        pthread_join(sim->philosopher_list[i].thread_id, NULL);
        i++;
    }
    destroy_mutexes(sim);
    free_dynamic_memory(sim);
}

void destroy_mutexes(t_simulation *sim)
{
    int i = 0; // Initialize counter variable

    while (i < sim->num_philosophers)
    {
        pthread_mutex_destroy(&sim->utensils[i]);
        i++; // Increment the counter
    }

    pthread_mutex_destroy(&sim->output_lock);
    pthread_mutex_destroy(&sim->meal_lock);
}


void free_dynamic_memory(t_simulation *sim)
{
    free(sim->utensils);
    free(sim->philosopher_list);
}

int create_philosopher_threads(t_simulation *sim)
{
    int i = 0; // Initialize counter variable

    while (i < sim->num_philosophers)
    {
        sim->philosopher_list[i].last_meal_time = get_time();
        if (pthread_create(&sim->philosopher_list[i].thread_id, NULL, philosopher_activity, &sim->philosopher_list[i]))
            return (1);
        i++; // Increment the counter
    }
    return 0;
}


int create_monitor_thread(t_simulation *sim)
{
    pthread_t monitor_thread;
    if (pthread_create(&monitor_thread, NULL, death_monitor, sim))
        return (1);
    pthread_join(monitor_thread, NULL);
    clean_up(sim);
    return (0);
}

int start_simulation(t_simulation *sim)
{
    sim->start_time = get_time();
    if (create_philosopher_threads(sim))
        return (1);
    return create_monitor_thread(sim);
}
