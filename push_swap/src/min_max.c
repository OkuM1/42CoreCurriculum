/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:57 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/05 15:38:09 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	find_min_index(t_list	*s)
{
	int		min_index;
	int		min_value;
	int		i;
	t_list	*temp;

	min_index = -1;
	min_value = 2147483647;
	temp = s;
	i = 0;
	while (1)
	{
		if (min_value > temp->data)
		{
			min_value = temp->data;
			min_index = i;
		}
		temp = temp->next;
		i++;
		if (temp == s)
			break ;
	}
	return (min_index);
}
