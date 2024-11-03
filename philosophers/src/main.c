/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:09:05 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/03 15:08:21 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Input validation function
int validate_input(t_simulation *sim, int argc, char *argv[]) {
    int i = 1;
    while (i < argc) {
        if (!ft_isnumber(argv[i]) || ft_atoi(argv[i]) < 0)
            return (0);
        i++;
    }
    sim->num_philosophers = ft_atoi(argv[1]);
    sim->die_time = ft_atoi(argv[2]);
    sim->eat_time = ft_atoi(argv[3]);
    sim->sleep_time = ft_atoi(argv[4]);

    if (argc == 6)
        sim->max_eat_count = ft_atoi(argv[5]);
    else 
        sim->max_eat_count = 0;
    
    return (sim->num_philosophers > 0 && sim->die_time >= 0 && sim->eat_time >= 0 && sim->sleep_time >= 0 && sim->max_eat_count >= 0);
}

// Mutex initialization
int initialize_utensils(t_simulation *sim) {
    if (pthread_mutex_init(&sim->output_lock, NULL) || pthread_mutex_init(&sim->meal_lock, NULL))
        return (1);
    
    int i = 0;
    while (i < sim->num_philosophers) {
        if (pthread_mutex_init(&sim->utensils[i], NULL))
            return (1);
        i++;
    }
    return (0);
}

int initialize_simulation(t_simulation *sim) {
    // Set up the simulation parameters
    sim->start_time = get_time();
    sim->is_over = 0;
    sim->all_fed = 0;

    int i = 0;
    // Initialize each philosopher using a while loop
    while (i < sim->num_philosophers) {
        sim->philosopher_list[i].index = i + 1;
        sim->philosopher_list[i].meal_count = 0;
        sim->philosopher_list[i].last_meal_time = get_time();
        sim->philosopher_list[i].sim = sim;

        sim->philosopher_list[i].left_fork = i;
        sim->philosopher_list[i].right_fork = (i + 1) % sim->num_philosophers;
        
        i++;
    }
    if (sim->num_philosophers <= 0)
        return 1;

    return 0;
}

int allocate_resources(t_simulation *sim) {
    sim->philosopher_list = malloc(sizeof(t_philosopher) * sim->num_philosophers);
    if (!sim->philosopher_list)
        return (0);
    
    sim->utensils = malloc(sizeof(pthread_mutex_t) * sim->num_philosophers);
    if (!sim->utensils) 
    {
        free(sim->philosopher_list);
        return (0);
    }
    return (1);
}

int main(int argc, char *argv[]) {
    t_simulation sim;

    if (argc < 5 || argc > 6)
        return (fprintf(stderr, "Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<max_eat_count>]\n"), 1);
    
    if (!validate_input(&sim, argc, argv))
        return (fprintf(stderr, "Invalid parameters.\n"), 1);

    if (!allocate_resources(&sim))
        return (fprintf(stderr, "Resource allocation error.\n"), 1);
    
    if (initialize_utensils(&sim))
        return (fprintf(stderr, "Utensil mutex initialization error.\n"), 1);
    
    if (initialize_simulation(&sim))
        return (fprintf(stderr, "Simulation initialization error.\n"), 1);
    
    if (start_simulation(&sim))
        return (fprintf(stderr, "Simulation start error.\n"), 1);
    

    return (0);
}
