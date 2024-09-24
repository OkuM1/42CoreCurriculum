/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:01:59 by afoth             #+#    #+#             */
/*   Updated: 2024/09/20 20:04:01 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	or_syntax(t_arg *head)
{
	t_arg	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == OR)
		{
			ft_putstr_fd("Syntax error: or '|| "
				"cannot be in the command\n", STDERR_FILENO);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
