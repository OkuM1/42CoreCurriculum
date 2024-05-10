/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_sorts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:38 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/06 13:13:41 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	tiny_sort(t_stack *s)
{
	t_list	*max_node;

	max_node = find_highest(s->head_a);
	if (s->head_a == max_node)
		ra(s);
	else if (s->head_a->next == max_node)
		rra(s);
	if (s->head_a->data > s->head_a->next->data)
		sa(s);
}

void	four_sort(t_stack *s)
{
	int	index;

	index = find_min_index(s->head_a);
	while (index != 0)
	{
		if (index < s->a_size / 2)
			ra(s);
		else
			rra(s);
		index = find_min_index(s->head_a);
	}
	pb(s);
	tiny_sort(s);
	pa(s);
}

void	five_sort(t_stack *s)
{
	int	index;

	index = find_min_index(s->head_a);
	while (index != 0)
	{
		if (index <= s->a_size / 2)
			ra(s);
		else
			rra(s);
		index = find_min_index(s->head_a);
	}
	pb(s);
	four_sort(s);
	pa(s);
}
