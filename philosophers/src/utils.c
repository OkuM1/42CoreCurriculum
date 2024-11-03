/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:54:30 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/03 15:29:22 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Convert a string to an integer
int ft_isnumber(const char *str) {
    if (!str || *str == '\0') return 0; // Check for empty string

    int i = 0;
    if (str[i] == '-' || str[i] == '+') i++; // Handle optional sign

    while (str[i]) {
        if (str[i] < '0' || str[i] > '9') return 0; // Not a digit
        i++;
    }
    return 1; // Valid integer string
}

// String to integer conversion
int ft_atoi(const char *str) {
    int sign = 1;
    long result = 0;

    while ((*str >= 9 && *str <= 13) || *str == ' ') str++; // Skip whitespace
    if (*str == '-' || *str == '+') {
        if (*str == '-') sign = -1;
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (int)(result * sign);
}

// Get the current time in milliseconds
long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

// Sleep for a specified duration in milliseconds
void new_sleep(int duration) {
    usleep(duration * 1000); // Convert milliseconds to microseconds
}
