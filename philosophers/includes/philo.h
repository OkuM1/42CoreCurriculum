/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:15:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/04 16:08:05 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

// Philosopher structure
typedef struct s_philosopher
{
	int					index;
	int					meal_count;
	long				last_meal_time;
	pthread_t			thread_id;
	struct s_simulation	*sim;
	int					left_fork;
	int					right_fork;
}						t_philosopher;

// Environment structure for managing philosophers
typedef struct s_simulation 
{
	long			num_philosophers;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			max_eat_count;
	pthread_mutex_t	*utensils;
	pthread_mutex_t	output_lock;
	pthread_mutex_t	meal_lock;
	long			start_time;
	int				is_over;
	int				all_fed;
	t_philosopher	*philosopher_list;
}					t_simulation;

// Function prototypes
int			main(int argc, char *argv[]);
int			validate_input(t_simulation *sim, int argc, char *argv[]);
int			initialize_utensils(t_simulation *sim);
int			allocate_resources(t_simulation *sim);
void		*philosopher_activity(void *params);
void		*philosopher_routine(t_philosopher *philo);
int			start_simulation(t_simulation *sim);
void		clean_up(t_simulation *sim);
void		*death_monitor(void *params);
long		get_time(void);
int			ft_isnumber(const char *str);
long long	ft_atoll(const char *str);

void		action_print(t_philosopher *philo, const char *msg);
void		pick_forks(t_philosopher *philo, int left_fork, int right_fork);
void		put_forks(t_philosopher *philo, int left_fork, int right_fork);
void		eat(t_philosopher *philo);
void		sleep_and_think(t_philosopher *philo);
void		check_for_death(t_simulation *sim, long time_to_die);
void		announce_death(t_simulation *sim, int index, long current_time);
void		destroy_mutexes(t_simulation *sim);
void		free_dynamic_memory(t_simulation *sim);
int			create_philosopher_threads(t_simulation *sim);
int			create_monitor_thread(t_simulation *sim);

#endif