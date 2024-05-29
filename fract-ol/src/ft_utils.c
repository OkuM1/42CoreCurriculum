/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:57:07 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/16 12:57:08 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isspace(int c)
{
	int	i;

	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r')
		i = 1;
	else
		i = 0;
	return (i);
}

static double	ft_div_atof(char *nptr, int sign)
{
	int		j;
	double	result;
	double	result2;

	j = 0;
	result = 0;
	result2 = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	if (*nptr == '.')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result2 = result2 * 10 + *nptr - '0';
		nptr++;
		j++;
	}
	result2 = result2 / pow(10, j);
	return ((result + result2) * sign);
}

double	ft_atof(char *nptr)
{
	int	j;
	int	sign;

	j = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	return (ft_div_atof(nptr, sign));
}
