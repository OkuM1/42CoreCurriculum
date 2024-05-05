/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_moves_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:28 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/05 15:38:23 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	ra(t_stack *s)
{
	if (!s->a_size)
		return ;
	s->head_a = s->head_a->next;
	write(1, "ra\n", 3);
}

void	rb(t_stack *s)
{
	if (!s->a_size)
		return ;
	s->head_b = s->head_b->next;
	write(1, "rb\n", 3);
}

void	rr(t_stack *s)
{
	if (!s->a_size || !s->b_size)
		return ;
	s->head_a = s->head_a->next;
	s->head_b = s->head_b->next;
	write(1, "rr\n", 3);
}

void	rra(t_stack *s)
{
	if (!s->a_size)
		return ;
	s->head_a = s->head_a->pre;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *s)
{
	if (!s->b_size)
		return ;
	s->head_b = s->head_b->pre;
	write(1, "rrb\n", 4);
}
