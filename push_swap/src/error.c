/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:21 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/21 15:59:19 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	ft_check_dup(int *tab, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (tab[i] == tab[j])
			{
				free(tab);
				return (0);
			}
			j++;
		}
		i++;
	}
	free(tab);
	return (1);
}

int	ft_duplicate(int ac, char **av)
{
	int		*tab;
	char	**numbers;
	int		i;
	int		j;
	int		count;

	i = 1;
	count = 0;
	while (i < ac)
	{
		j = 0;
		numbers = ft_split(av[i], ' ');
		while (numbers[j++])
			count++;
		free_split(numbers);
		i++;
	}
	tab = (int *)malloc(sizeof(int) * count);
	if (!tab)
		return (0);
	ft_tab_init(ac, av, tab);
	return (ft_check_dup(tab, count));
}

int	ft_digit(char *number)
{
	size_t	i;

	i = 0;
	if (!number[i])
		return (0);
	if (number[i] == '+' || number[i] == '-')
		i++;
	while (number[i])
	{
		if (!ft_isdigit(number[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_num(char **numbers)
{
	size_t	i;

	i = 0;
	if (!numbers[i])
		return (0);
	while (numbers[i])
	{
		if (!ft_digit(numbers[i]) || ((!ft_atoi(numbers[i]) && \
		ft_strncmp(numbers[i], "-0", 2) && ft_strncmp(numbers[i], "+0", 2)) \
		&& ft_strncmp(numbers[i], "0", 1)))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_error(int ac, char **av)
{
	int		i;
	char	**numbers;

	i = 1;
	while (i < ac)
	{
		numbers = ft_split(av[i], ' ');
		if (!ft_check_num(numbers))
		{
			free_split(numbers);
			return (0);
		}
		free_split(numbers);
		i++;
	}
	if (!ft_duplicate(ac, av))
		return (0);
	return (1);
}
