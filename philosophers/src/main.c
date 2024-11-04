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
int	validate_input(t_simulation *sim, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isnumber(argv[i]) || ft_atoll(argv[i]) < 0)
			return (0);
		i++;
	}
	sim->num_philosophers = ft_atoll(argv[1]);
	sim->die_time = ft_atoll(argv[2]);
	sim->eat_time = ft_atoll(argv[3]);
	sim->sleep_time = ft_atoll(argv[4]);
	if (argc == 6)
		sim->max_eat_count = ft_atoll(argv[5]);
	else 
		sim->max_eat_count = -1;
	if (argc == 6 && sim->max_eat_count < 0)
		return (0);
	return (sim->num_philosophers > 0 && sim->die_time >= 0 
		&& sim->eat_time >= 0 && sim->sleep_time >= 0);
}

// Mutex initialization
int	initialize_utensils(t_simulation *sim)
{
	int	i;

	if (pthread_mutex_init(&sim->output_lock, NULL) 
		|| pthread_mutex_init(&sim->meal_lock, NULL))
		return (1);
	i = 0;
	while (i < sim->num_philosophers)
	{
		if (pthread_mutex_init(&sim->utensils[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

// sim->philosopher_list[i].left_fork = i;
// sim->philosopher_list[i].right_fork = (i + 1) % sim->num_philosophers;
int	initialize_simulation(t_simulation *sim)
{
	int	i;

	sim->start_time = get_time();
	sim->is_over = 0;
	sim->all_fed = 0;
	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosopher_list[i].index = i + 1;
		sim->philosopher_list[i].meal_count = 0;
		sim->philosopher_list[i].last_meal_time = get_time();
		sim->philosopher_list[i].sim = sim;
		i++;
	}
	if (sim->num_philosophers <= 0)
		return (1);
	return (0);
}

int	allocate_resources(t_simulation *sim)
{
	sim->philosopher_list = malloc(sizeof(t_philosopher) 
			* sim->num_philosophers);
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

int	main(int argc, char *argv[])
{
	t_simulation	sim;

	if (argc < 5 || argc > 6)
		return (printf("Usage: ./philo <number_of_philosophers> "
				"<time_to_die> <time_to_eat> <time_to_sleep> "
				"[<number_of_times_each_philosopher_must_eat>]\n"));
	if (!validate_input(&sim, argc, argv))
		return (printf("Invalid parameters.\n"));
	if (!allocate_resources(&sim))
		return (printf("Resource allocation error.\n"));
	if (initialize_utensils(&sim))
		return (printf("Utensil mutex initialization error.\n"));
	if (initialize_simulation(&sim))
		return (printf("Simulation initialization error.\n"));
	if (start_simulation(&sim))
		return (printf("Simulation start error.\n"));
	return (0);
}
