/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:01 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/05 15:37:01 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libs/libft/libft.h"

typedef struct s_stack
{
	t_list	*head_a;
	t_list	*head_b;
	int		*sorted;
	int		a_size;
	int		b_size;
}t_stack;

t_list	*find_highest(t_list *head);
int		find_min_index(t_list *s);
int		ft_check_error(int ac, char **av);
int		ft_is_sorted(t_stack *s);
void	free_split(char **numbers);
void	ft_tab_init(int ac, char **av, int *tab);
void	ft_stack_init(t_stack *sa, int ac, char **av);
void	ft_push_back(t_stack *sa, char *number);
void	delete_head_b(t_stack *sa);
void	delete_head_a(t_stack *sa);
void	ft_free_init(t_stack *s);
void	tiny_sort(t_stack *s);
void	four_sort(t_stack *s);
void	five_sort(t_stack *s);
void	radix_sort(t_stack *s);
void	sa(t_stack *sa);
void	pa(t_stack *sa);
void	pb(t_stack *sa);
void	ra(t_stack *s);
void	rb(t_stack *s);
void	rra(t_stack *s);

#endif