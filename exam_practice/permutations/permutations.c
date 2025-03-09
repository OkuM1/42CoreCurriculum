/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:27:37 by mokutucu          #+#    #+#             */
/*   Updated: 2025/03/09 15:19:51 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:27:37 by mokutucu          #+#    #+#             */
/*   Updated: 2025/03/09 14:28:56 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "permutations.h"

void	swap_letters(char *str, int i, int j)
{
	char	tmp;

	while (j > i)
	{
		tmp = str[j];
		str[j] = str[j - 1];
		str[j - 1] = tmp;
		j--;
	}
}

void	restore_letters(char *str, int i, int j)
{
	char	tmp;

	while (i < j)
	{
		tmp = str[i];
		str[i] = str[i + 1];
		str[i + 1] = tmp;
		i++;
	}
}

void	generate_permutations(char *str, int start, int end)
{
	int i = start;

	if (start == end)
		printf("result: %s\n", str);
	else
	{
		while (i <= end)
		{
			swap_letters(str, start, i);
			generate_permutations(str, start + 1, end);
			restore_letters(str, start, i);
			i++;
		}
	}
}

int	string_length(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i - 1);
}

int	find_min_index(char *str, int i)
{
	int min = i;

	while (str[i])
	{
		if (str[i] < str[min])
			min = i;
		i++;
	}
	return (min);
}

void	sort_letters(char *str)
{
	int i = 0;

	while (str[i])
	{
		int j = find_min_index(str, i);
		swap_letters(str, i, j);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int n = string_length(av[1]);
	sort_letters(av[1]);
	generate_permutations(av[1], 0, n);
	return (0);
}
