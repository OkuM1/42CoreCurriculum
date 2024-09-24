/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:09:04 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/20 20:04:35 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Check list for syntax errors and return 1 if there is an error
int	syntax_checker(t_arg *head)
{
	if (!head)
	{
		return (1);
	}
	if (pipe_syntax(head))
	{
		return (1);
	}
	if (redirection_syntax(head))
	{
		return (1);
	}
	if (or_syntax(head))
	{
		return (1);
	}
	return (0);
}
