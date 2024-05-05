/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_moves_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:33 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/05 15:38:28 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	rrr(t_stack *s)
{
	if (!s->a_size || !s->b_size)
		return ;
	s->head_a = s->head_a->pre;
	s->head_b = s->head_b->pre;
	write(1, "rrr\n", 4);
}
