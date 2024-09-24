/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:15:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/24 18:17:22 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
    int philo_id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_eats;
    int left_fork;
    int right_fork;
}              t_philo;

# endif