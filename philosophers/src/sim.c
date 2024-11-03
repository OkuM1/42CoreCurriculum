/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:12:57 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/03 16:59:24 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *philosopher_activity(void *params)
{
    t_philosopher *philo = (t_philosopher *)params;
    t_simulation *sim = philo->sim;
    
    // Initial setup to handle odd philosophers starting with a sleep to stagger their actions
    if (philo->index % 2 == 0 && sim->num_philosophers > 1)
        usleep(sim->eat_time / 50); // Sleep a bit to avoid contention for forks

    while (!sim->is_over)
    {
        // Attempt to take forks (utensils) 
        pthread_mutex_lock(&sim->utensils[philo->index - 1]); // Lock the left fork
        pthread_mutex_lock(&sim->utensils[philo->index % sim->num_philosophers]); // Lock the right fork
        
        // Eating
        pthread_mutex_lock(&sim->output_lock); // Lock before printing
        printf("Philosopher %d is eating\n", philo->index);
        pthread_mutex_unlock(&sim->output_lock); // Unlock after printing
        philo->last_meal_time = get_time(); // Update last meal time
        usleep(sim->eat_time * 1000); // Simulate eating duration
        
        // Release forks
        pthread_mutex_unlock(&sim->utensils[philo->index - 1]); // Unlock the left fork
        pthread_mutex_unlock(&sim->utensils[philo->index % sim->num_philosophers]); // Unlock the right fork
        
        // Sleeping
        pthread_mutex_lock(&sim->output_lock); // Lock before printing
        printf("Philosopher %d is sleeping\n", philo->index);
        pthread_mutex_unlock(&sim->output_lock); // Unlock after printing
        usleep(sim->sleep_time * 1000); // Simulate sleeping duration
        
        // Thinking
        pthread_mutex_lock(&sim->output_lock); // Lock before printing
        printf("Philosopher %d is thinking\n", philo->index);
        pthread_mutex_unlock(&sim->output_lock); // Unlock after printing
    }
    
    return NULL; // Not strictly necessary, but included for completeness
}

void *death_monitor(void *params)
{
    t_simulation *sim = (t_simulation *)params;
    long time_to_die = sim->die_time; // Maximum time a philosopher can go without eating
    int i = 0; // Initialize index

    while (1)
    {
        // Initialize a flag to check if any philosopher is dead
        int dead_philosopher_found = 0;

        // Check each philosopher's last meal time using a while loop
        while (i < sim->num_philosophers)
        {
            long current_time = get_time();
            if (current_time - sim->philosopher_list[i].last_meal_time > time_to_die)
            {
                pthread_mutex_lock(&sim->output_lock);
                printf("Philosopher %d has died\n", sim->philosopher_list[i].index);
                sim->is_over = 1; // Set the simulation to over
                pthread_mutex_unlock(&sim->output_lock);
                dead_philosopher_found = 1; // Mark that a philosopher has died
                break; // Exit the inner loop since we've found a dead philosopher
            }
            i++; // Increment index
        }

        if (dead_philosopher_found)
            break; // Exit the while loop if a philosopher died

        usleep(100); // Sleep for a short duration before checking again

        // Reset index for the next iteration
        i = 0; // Reset index to check all philosophers again
    }
    return NULL; // Not strictly necessary, but included for completeness
}

void clean_up(t_simulation *sim)
{
    int i = 0;
    // Join philosopher threads
    while (i < sim->num_philosophers)
    {
        pthread_join(sim->philosopher_list[i].thread_id, NULL); // Join each philosopher thread
        i++;
    }
    
    // Destroy mutexes and free resources
    i = 0;
    while (i < sim->num_philosophers)
    {
        pthread_mutex_destroy(&sim->utensils[i]);
        i++;
    }
    pthread_mutex_destroy(&sim->output_lock);
    pthread_mutex_destroy(&sim->meal_lock);
    free(sim->utensils);
    free(sim->philosopher_list);
}


// Thread creation and simulation start
int start_simulation(t_simulation *sim)
{
    int i;
    
    i = 0;
    while (i < sim->num_philosophers)
    {
        if (pthread_create(&sim->philosopher_list[i].thread_id, NULL, philosopher_activity, &sim->philosopher_list[i]))
            return (1);
        i++;
    }
    
    // Start the death monitor thread
    pthread_t monitor_thread;
    if (pthread_create(&monitor_thread, NULL, death_monitor, sim))
        return (1);

    // Optionally join the monitor thread if you need to wait for it to finish later
    pthread_detach(monitor_thread); // Detach the monitor thread
    clean_up(sim); // Ensure resources are cleaned up after the simulation
    return (0);
}