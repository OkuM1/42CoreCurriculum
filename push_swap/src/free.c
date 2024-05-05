/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:26 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/05 15:37:51 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	free_split(char **numbers)
{
	size_t	i;

	if (!numbers)
		return ;
	i = 0;
	while (numbers[i])
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

void	ft_free_init(t_stack *s)
{
	t_list	*temp;
	t_list	*next_node;

	temp = s->head_a;
	while (1)
	{
		next_node = temp->next;
		free(temp);
		temp = next_node;
		if (temp == s->head_a)
			break ;
	}
	s->a_size = 0;
	s->head_a = NULL;
	exit(0);
}
