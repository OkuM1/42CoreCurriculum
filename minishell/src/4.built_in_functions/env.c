/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:43:12 by mokutucu          #+#    #+#             */
/*   Updated: 2024/09/22 16:03:20 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Function to print environment variables
int	built_in_env(t_shell *shell)
{
	char	**env;

	env = shell->env;
	if (shell->cmds_head->args || shell->cmds_head->flags)
	{
		ft_putstr_fd("env: no options allowed\n", STDERR_FILENO);
		return (1);
	}
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
