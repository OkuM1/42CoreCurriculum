/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:55:31 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/20 20:01:32 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_syntax(t_arg *head)
{
	t_arg	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next || !tmp->prev)
			{
				write (STDERR_FILENO,
					"Syntax error: pipe '|' cannot be"
					"at the beginning or end of the command\n", 72);
				return (1);
			}
			if (tmp->next->type == PIPE || tmp->prev->type == PIPE)
			{
				write (STDERR_FILENO, "Syntax error:"
					" consecutive pipes '||' are not allowed\n", 54);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
