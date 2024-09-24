/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:43:12 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/17 23:29:46 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to print environment variables
int	built_in_env(t_shell *shell)
{
	char	**env;

	env = shell->env;
	if (!env)
	{
		return (1);
	}
	while (*env)
	{
		if (write(STDOUT_FILENO, *env, ft_strlen(*env)) == -1)
			return (1);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (1);
		env++;
	}
	return (0);
}
