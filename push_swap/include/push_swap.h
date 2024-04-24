/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:02:09 by mokutucu          #+#    #+#             */
/*   Updated: 2024/04/24 18:05:07 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

//struct for stack
typedef struct s_stack
{
	int	*stack;
	int	size;
}	t_stack;

//struct for operations
typedef struct s_operations
{
	char	*operation;
	void	(*f)(t_stack *a, t_stack *b);
}	t_operations;

//struct for sorting
typedef struct s_sort
{
	int	*sorted;
	int	size;
}	t_sort;

//struct for push_swap
typedef struct s_push_swap
{
	t_stack	*a;
	t_stack	*b;
	t_sort	*sort;
}	t_push_swap;

//functions for stack
t_stack	*stack_init(int size);

//functions for operations
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);


#endif
